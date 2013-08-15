//
//  query_result.hpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef core_query_result_hpp
#define core_query_result_hpp

#include "sql_field.hpp"
#include "non_movable.hpp"
#include <libpq/libpq-fe.h>
#include <unordered_map>
#include <vector>
#include <boost/noncopyable.hpp>

struct sql_statement : boost::noncopyable
{
    PGresult * res = nullptr;
    int field_count, row_count, ntuple = 0;

    sql_statement() = default;

    sql_statement(PGresult * res, int field_count, int row_count) : res { res },
        field_count { field_count }, row_count { row_count }
    {
    }

    sql_statement(sql_statement && other)
    {
        res = other.res;
        field_count = other.field_count;
        row_count = other.row_count;
        ntuple = other.ntuple;
        other.res = nullptr;
        other.field_count = other.row_count = other.ntuple = 0;
    }

    ~sql_statement()
    { PQclear(res); }
};

using field_map = std::unordered_map<std::string, sql_field>;

/* implicitly non copyable but implicitly movable */
class query_result
{
private:
    std::vector<sql_statement> _results;
    field_map _current_row;
    int _current_statement = -1;

public:
    query_result() = default;
    explicit query_result(std::vector<sql_statement>);
    bool next_row();
    bool next_statement();
    int field_count() const;
    int row_count() const;

    explicit operator bool() const
    { return !_results.empty(); }

    const field_map & fetch() const
    { return _current_row; }
};

#endif
