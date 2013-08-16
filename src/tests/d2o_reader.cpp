//
//  d2o_reader.cpp
//  tests
//
//  Created by Alexandre Martin on 16/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "../core/common.hpp"
#include "../d2fstream/d2o_reader.hpp"
#include "../d2fstream/data_holder.hpp"
#include "../d2fstream/datacenter/anim_fun_data.hpp"
#include "../d2fstream/datacenter/monsters/anim_fun_monster_data.hpp"
#include "../d2fstream/datacenter/monsters/monster_drop.hpp"
#include "../d2fstream/datacenter/monsters/monster_grade.hpp"
#include "../d2fstream/datacenter/monsters/monster.hpp"
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(d2o_reader_suite)

BOOST_AUTO_TEST_CASE(misc)
{
    d2o_reader d2o { std::ifstream { "Monsters.d2o", std::ios::binary } };
    datacenter::monster m = d2o.read_object(101);
    BOOST_REQUIRE_EQUAL( m.name_id, 6817 );
    BOOST_REQUIRE_EQUAL( m.grades[0].level, 13 );
}

BOOST_AUTO_TEST_SUITE_END()