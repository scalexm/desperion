//
//  d2i_reader.cpp
//  tests
//
//  Created by Alexandre Martin on 16/08/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#include "../core/common.hpp"
#include "../d2fstream/d2i_reader.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(d2i_reader_suite)

BOOST_AUTO_TEST_CASE(d2i_reader_misc)
{
    d2i_reader d2i { std::ifstream { "/Users/alexm/Desktop/i18n_fr.d2i", std::ios::binary } };
    BOOST_REQUIRE_EQUAL( d2i.read_text(47007), "Rune Ra Ini" );
    BOOST_REQUIRE_EQUAL( d2i.read_ui_text("ui.alert.event.1"), "Connexion d'un ami" );
}

BOOST_AUTO_TEST_SUITE_END()