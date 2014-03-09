//
//  d2o_reader.cpp
//  tests
//
//  Created by Alexandre Martin on 16/08/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#include "../core/common.hpp"
#include "../d2fstream/d2o_reader.hpp"
/*#include "../d2fstream/data_holder.hpp"
#include "../d2fstream/datacenter/anim_fun_data.hpp"
#include "../d2fstream/datacenter/monsters/anim_fun_monster_data.hpp"
#include "../d2fstream/datacenter/monsters/monster_drop.hpp"
#include "../d2fstream/datacenter/monsters/monster_grade.hpp"
#include "../d2fstream/datacenter/monsters/monster.hpp"*/
#include <boost/test/unit_test.hpp>
#include <chrono>

BOOST_AUTO_TEST_SUITE(d2o_reader_suite)

BOOST_AUTO_TEST_CASE(d2o_reader_misc)
{
    auto t = std::chrono::system_clock::now();
    d2o_reader d2o { std::ifstream { "/Users/alexm/Desktop/Items.d2o", std::ios::binary } };
    std::cout << (std::chrono::system_clock::now() - t).count() << std::endl;
    auto a = d2o.read_all_objects();
    std::cout << (std::chrono::system_clock::now() - t).count() << std::endl;
    /*datacenter::monster m = d2o.read_object(101);
    BOOST_REQUIRE_EQUAL( m.name_id, 6817 );
    BOOST_REQUIRE_EQUAL( m.grades[0].level, 13 );*/
}

BOOST_AUTO_TEST_SUITE_END()