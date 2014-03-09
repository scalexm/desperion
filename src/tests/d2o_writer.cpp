//
//  d2o_writer.cpp
//  tests
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#include "../core/common.hpp"
#include "../d2fstream/d2o_writer.hpp"
#include "../d2fstream/d2o_reader.hpp"
//#include "../d2fstream/data_holder.hpp"
#include "../d2fstream/d2o_class_definition.hpp"
#include <boost/test/unit_test.hpp>
#include <fstream>

/*struct test : data_holder
{
    std::vector<test> a;
    std::string b;

    test() = default;

    test(data_object && data)
    {
        acquire(a, data.second.at("a"));
        acquire(b, data.second.at("b"));
    }

    data_object to_d2o(const d2o_writer & file)
    {
        data_object data;
        data.first = file.get_class_id_for_type<test>();
        release(a, data.second["a"], file);
        release(b, data.second["b"], file);
        return data;
    }
};*/

BOOST_AUTO_TEST_SUITE(d2o_writer_suite)

BOOST_AUTO_TEST_CASE(d2o_writer_misc)
{
    /*d2o_writer writer;
    d2o_class_definition test_class { "test", "desperion.test" };
    test_class.bind_cpp_type<test>();
    test_class.add_field(d2o_field { "a", D2O_FIELD_TYPE_VECTOR, { { "", 545 } } });
    test_class.add_field(d2o_field { "b", D2O_FIELD_TYPE_STRING, { } });
    writer.add_class_definition(1, test_class);

    test test1, test2;
    test1.b = "salut";
    test2.b = "yo mec";
    test2.a.push_back(test1);
    writer.add_object(54, test2.to_d2o(writer));
    writer.write(std::ofstream { "test.d2o", std::ios::binary });

    d2o_reader reader { std::ifstream { "test.d2o", std::ios::binary } };
    test t = reader.read_object(54);
    BOOST_REQUIRE_EQUAL( t.b, "yo mec" );
    BOOST_REQUIRE_EQUAL( t.a.size(), 1);
    BOOST_REQUIRE_EQUAL( t.a[0].b, "salut" );*/

}

BOOST_AUTO_TEST_SUITE_END()
