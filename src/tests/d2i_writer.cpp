//
//  d2i_writer.cpp
//  tests
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#include "../core/common.hpp"
#include "../d2fstream/d2i_writer.hpp"
#include "../d2fstream/d2i_reader.hpp"
#include <boost/test/unit_test.hpp>
#include <fstream>

BOOST_AUTO_TEST_SUITE(d2i_writer_suite)

BOOST_AUTO_TEST_CASE(d2i_writer_misc)
{
    d2i_writer writer;
    writer.add_text(1, "salut");
    writer.add_text(2, "yo");
    writer.add_ui_text("hey", "abc");
    writer.add_ui_text("hello", "how are you");
    writer.write(std::ofstream { "test.d2i", std::ios::binary });

    d2i_reader d2i { std::ifstream { "test.d2i", std::ios::binary } };
    BOOST_REQUIRE_EQUAL( d2i.read_all_text()[2], "yo" );
    BOOST_REQUIRE_EQUAL( d2i.read_all_ui_text()["hey"], "abc" );
}

BOOST_AUTO_TEST_SUITE_END()
