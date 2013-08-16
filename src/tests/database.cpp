//
//  database.cpp
//  tests
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "../core/common.hpp"
#include "../core/sql_database.hpp"
#include "../core/sql_error.hpp"
#include "../core/query_result.hpp"
#include <boost/test/unit_test.hpp>
#include <fstream>

BOOST_AUTO_TEST_SUITE(sql_database_suite)

BOOST_AUTO_TEST_CASE(misc)
{
    boost::asio::io_service ios;
    sql_database db { 2, ios };
    std::ifstream file { "password.txt" };
    std::ostringstream password;
    password << file.rdbuf();
    db.init("localhost", 5432, "postgres", password.str(), "desperion");
    std::unordered_map<std::string, std::string> queries;
    queries.emplace("t1", R"(INSERT INTO "test" VALUES($1, $2);)");
    queries.emplace("t2", R"(SELECT * FROM "test";)");
    queries.emplace("t3", R"(DELETE FROM "test";)");
    db.load_queries(queries);

    db.query({ sql_database::prepare("t1", "salut", 45) });

    db.async_query([](result_ptr & result, const std::string & err)
                   {
                       if (err != "")
                           throw sql_error { err };
                       BOOST_REQUIRE( *result );
                       auto && fields = result->fetch();
                       BOOST_REQUIRE_EQUAL( fields.at("a").get<std::string>(), "salut" );
                       BOOST_REQUIRE_EQUAL( fields.at("b").get<int>(), 45 );
                   }, { sql_database::prepare("t2") });

    ios.run();

    db.query({ sql_database::prepare("t3") });
    auto result = db.query({ sql_database::prepare("t2") });
    BOOST_REQUIRE( !result );
}

BOOST_AUTO_TEST_SUITE_END();