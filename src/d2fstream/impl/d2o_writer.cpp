//
//  d2o_writer.cpp
//  d2fstream
//
//  Created by Alexandre Martin on 31/07/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#include "../../core/common.hpp"
#include "d2o_writer_impl.hpp"

d2o_writer::d2o_writer() : _impl { this }
{
}

d2o_writer::~d2o_writer()
{
    // willingly empty
}

void d2o_writer::add_class_definition(int id, const d2o_class_definition & c)
{
    _impl->add_class_definition(id, c);
}

void d2o_writer::add_object(int id, data_object && obj)
{
    _impl->add_object(id, std::move(obj));
}

int d2o_writer::get_class_id_for_hash(size_t hash) const
{
    return _impl->get_class_id_for_hash(hash);
}

const d2o_class_definition & d2o_writer::get_class_definition(int id) const
{
    return _impl->get_class_definition(id);
}

bool d2o_writer::has_class_definition(int id) const
{
    return _impl->has_class_definition(id);
}

void d2o_writer::write(std::ofstream & file) const
{
    _impl->write(file);
}

void d2o_writer::write(std::ofstream && file) const
{
    write(file);
}
