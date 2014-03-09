//
//  d2o_reader.cpp
//  d2fstream
//
//  Created by Alexandre Martin on 31/07/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#include "../../core/common.hpp"
#include "d2o_reader_impl.hpp"

d2o_reader::d2o_reader(std::ifstream & file) : _impl { file, this }
{
}

d2o_reader::d2o_reader(std::ifstream && file) : d2o_reader { file }
{
}

d2o_reader::~d2o_reader()
{
    // willingly empty
}

const d2o_class_definition & d2o_reader::get_class_definition(int class_id) const
{
    return _impl->get_class_definition(class_id);
}

bool d2o_reader::has_class_definition(int class_id) const
{
    return _impl->has_class_definition(class_id);
}

data_object d2o_reader::read_object(int index)
{
    return _impl->read_object(index);
}

std::unordered_map<int, data_object> d2o_reader::read_all_objects()
{
    return _impl->read_all_objects();
}
