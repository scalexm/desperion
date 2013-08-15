//
//  sql_database.cpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "../common.hpp"
#include "../scope_guard.hpp"
#include "../sql_database.hpp"
#include "../query_result.hpp"
#include "../run_service.hpp"
#include "../sql_error.hpp"
#include "../utils.hpp"

auto sql_database::get_free_connection() -> connection &
{
    auto i = 0;
    while (true)
    {
        auto & c = _connections[(i++) % _connections.size()];
        if (c.lock.try_lock())
            return c;
        if (i % 20 == 0)
            std::this_thread::sleep_for(std::chrono::milliseconds { 10 } );
    }
    // never reached
}

sql_database::sql_database(uint8_t size, boost::asio::io_service & ms) : _connections { size },
    _main_service(ms)
{
    _work = std::make_unique<boost::asio::io_service::work>(_service);
    _thread = std::make_unique<std::thread>(std::bind(run_service, std::ref(_service)));
}

sql_database::~sql_database()
{
    _work.reset();
    _thread->join();
}

void sql_database::init(const std::string & host, uint16_t port, const std::string & user,
                        const std::string & password, const std::string & name)
{
    for (auto && c : _connections)
    {
        auto temp = PQsetdbLogin(host.c_str(), boost::lexical_cast<std::string>(port).c_str(),
                                 nullptr, nullptr, name.c_str(), user.c_str(), password.c_str());
        auto guard = make_guard(std::bind(&PQfinish, temp));
        if (PQstatus(temp) == CONNECTION_BAD)
            throw sql_error { "connection failed due to: "_s + PQerrorMessage(temp) };
        guard.dismiss();
        if (c.conn != nullptr)
            PQfinish(c.conn);
        c.conn = temp;
    }
}

void sql_database::load_queries(const std::unordered_map<std::string, std::string> & queries)
{
    auto & c = get_free_connection();
    auto guard = make_guard(std::bind(&std::mutex::unlock, &c.lock));
    for(auto && it : queries)
    {
        auto res = PQprepare(c.conn, it.first.c_str(), it.second.c_str(), 0, nullptr);
        auto res_guard = make_guard(std::bind(PQclear, res));
        auto status = PQresultStatus(res);
        if (status == PGRES_FATAL_ERROR)
        {
            throw sql_error { "sql query failed due to "_s + PQresultErrorMessage(res)
                + ", query: " + it.first };
        }
    }
}

query_result sql_database::send_query(connection & c, const query_list & sql, std::string & error)
{
    if (sql.size() > 1)
        PQclear(PQexec(c.conn, "BEGIN;"));

    std::vector<sql_statement> results;
    for (auto && query : sql)
    {
        std::vector<const char *> args;
        for (auto && arg : query.args)
            args.push_back(arg.c_str());
        auto res = PQexecPrepared(c.conn, query.name.c_str(), args.size(), args.data(),
                                  nullptr, nullptr, 0);
        auto status = PQresultStatus(res);
        if (status == PGRES_FATAL_ERROR)
        {
            if (sql.size() > 1)
                PQclear(PQexec(c.conn, "ROLLBACK;"));
            error = "sql query failed due to "_s + PQresultErrorMessage(res)
                + ", query: " + query.name;
            PQclear(res);
            break;
        }
        else if (status == PGRES_TUPLES_OK && PQntuples(res) > 0)
            results.emplace_back(res, PQnfields(res), PQntuples(res));
        else
            PQclear(res);
    }

    if (sql.size() > 1)
        PQclear(PQexec(c.conn, "COMMIT;"));
    if (!results.empty())
        return query_result { std::move(results) };
    return { };
}

void sql_database::async_send_query(boost::asio::io_service::work &,
                                    sql_callback cb, const query_list & sql)
{
    auto & c = get_free_connection();
    auto guard = make_guard(std::bind(&std::mutex::unlock, &c.lock));
    std::string error;
    auto qres = std::make_shared<query_result>(send_query(c, sql, error));
    _main_service.post(std::bind(cb, std::move(qres), error));
}

query_result sql_database::query(const query_list & sql)
{
    if (sql.empty())
        return { };
    auto & c = get_free_connection();
    auto guard = make_guard(std::bind(&std::mutex::unlock, &c.lock));
    std::string error;
    auto result = send_query(c, sql, error);
    if (!error.empty())
        throw sql_error { error.c_str() };
    return result;
}

void sql_database::async_query(sql_callback cb, query_list sql)
{
    if(sql.empty())
        return;
    /* giving work to _main_service */
    _service.post(std::bind(&sql_database::async_send_query,
                            this,
                            boost::asio::io_service::work { _main_service },
                            cb,
                            std::move(sql)));
}
