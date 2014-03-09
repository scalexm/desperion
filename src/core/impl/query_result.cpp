//
//  query_result.cpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#include "../common.hpp"
#include "../query_result.hpp"

query_result::query_result(std::vector<sql_statement> results)
    : _results { std::move(results) }
{
    next_statement();
}

bool query_result::next_row()
{
    auto & stmt = _results[_current_statement];
    if (stmt.ntuple == stmt.row_count)
        return false;
    for (int col = 0; col < stmt.field_count; ++col)
        _current_row[PQfname(stmt.res, col)] = sql_field { PQgetvalue(stmt.res, stmt.ntuple, col) };
    ++stmt.ntuple;
    return true;
}

bool query_result::next_statement()
{
    if (++_current_statement >= _results.size())
        return false;
    _current_row.clear();
    next_row();
    return true;
}

int query_result::field_count() const
{
    return _results[_current_statement].field_count;
}

int query_result::row_count() const
{
    return _results[_current_statement].row_count;
}
