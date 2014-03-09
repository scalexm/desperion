//
//  sql_database.hpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#ifndef core_sql_database_hpp
#define core_sql_database_hpp

#include "non_movable.hpp"
#include <string>
#include <vector>
#include <list>
#include <functional>
#include <libpq/libpq-fe.h>
#include <boost/asio.hpp>
#include <thread>
#include <unordered_map>
#include <boost/lexical_cast.hpp>

class query_result;

struct sql_query
{
    std::string name;
    std::vector<std::string> args;

    sql_query(std::string name) : name { std::move(name) }
    {
    }
};

using query_list = std::list<sql_query>;
using result_ptr = std::shared_ptr<query_result>;

// sql_database only uses prepared statements
class sql_database : non_movable
{
public:
    using sql_callback = std::function<void(result_ptr &, const std::string &)>;

private:
    struct connection : non_movable
    {
        PGconn * conn = nullptr;
        std::mutex lock;

        connection() = default;

        ~connection()
        {
            if(conn)
                PQfinish(conn);
        }
    };

    boost::asio::io_service _service, & _main_service;
    std::unique_ptr<boost::asio::io_service::work> _work;
    std::unique_ptr<std::thread> _thread;
    std::vector<connection> _connections;
    
    query_result send_query(connection &, const query_list &, std::string &);
    void async_send_query(boost::asio::io_service::work & work, sql_callback &, const query_list &);
    connection & get_free_connection();

    template<class T>
    static void build_query(sql_query & q, const T & value)
    {
        q.args.push_back(boost::lexical_cast<std::string>(value));
    }

    template<class T, class ... Args>
    static void build_query(sql_query & q, const T & value, const Args & ... args)
    {
        q.args.push_back(boost::lexical_cast<std::string>(value));
        build_query(q, args...);
    }
    
public:
    sql_database(uint8_t, boost::asio::io_service &);
    ~sql_database();
    void init(const std::string &, uint16_t, const std::string &, const std::string &,
              const std::string &);
    void load_queries(const std::unordered_map<std::string, std::string> &);

    query_result query(const query_list &);
    void async_query(sql_callback, query_list);

    // helper method to create prepared statements easily
    template<class ... Args>
    static sql_query prepare(std::string name, const Args & ... args)
    {
        sql_query q { std::move(name) };
        build_query(q, args...);
        return q;
    }

    static sql_query prepare(std::string name)
    { return { std::move(name) }; }
};

#endif
