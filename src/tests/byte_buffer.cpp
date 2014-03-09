//
//  byte_buffer.cpp
//  tests
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#include "../core/common.hpp"
#include "../core/byte_buffer.hpp"
#include "../core/utils.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(byte_buffer_suite)

BOOST_AUTO_TEST_CASE(byte_buffer_misc)
{
    byte_buffer b;
    BOOST_REQUIRE_EQUAL( b.size(), 0 );
    
    b << 5 << 8 << uint8_t { 5 } << "salut"_s << 2.71828;
    BOOST_REQUIRE_EQUAL( b.size(), 24 );
    
    int v1, v2;
    uint8_t v3;
    std::string v4;
    double v5;
    b >> v1 >> v2 >> v3 >> v4 >> v5;
    BOOST_REQUIRE_EQUAL( v1, 5 );
    BOOST_REQUIRE_EQUAL( v2, 8 );
    BOOST_REQUIRE_EQUAL( v3, 5 );
    BOOST_REQUIRE_EQUAL( v4, "salut" );
    BOOST_REQUIRE_EQUAL( v5, 2.71828 );

    b.seekp(4);
    b << 25;
    b.seekg(4);
    b >> v2;
    BOOST_REQUIRE_EQUAL( v2, 25 );
    
    b.clear();
    BOOST_REQUIRE_EQUAL( b.size(), 0 );
}

BOOST_AUTO_TEST_SUITE_END()
