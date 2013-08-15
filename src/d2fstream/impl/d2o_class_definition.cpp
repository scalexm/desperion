//
//  d2o_class_definition.cpp
//  d2fstream
//
//  Created by Alexandre Martin on 31/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "../../core/common.hpp"
#include "../d2o_class_definition.hpp"
#include "../../core/byte_buffer.hpp"

d2o_class_definition::d2o_class_definition(std::string name, std::string package_name)
    : _name { std::move(name) }, _package_name { std::move(package_name) }
{
}

d2o_class_definition::d2o_class_definition(std::string name, std::string package_name,
                                           byte_buffer & buffer)
    : _name { std::move(name) }, _package_name { std::move(package_name) }
{
    int count;
    buffer >> count;
    for (auto a = 0; a < count; ++a)
    {
        std::string name;
        int type;
        buffer >> name >> type;
        _fields.emplace_back(std::move(name), type, buffer);
    }
}

data_fields d2o_class_definition::read(d2o_reader * owner, byte_buffer & buffer) const
{
    data_fields fields;
    for (auto && it : _fields)
        fields.emplace(it.name(), it.read(owner, buffer));
    return fields;
}

void d2o_class_definition::add_field(const d2o_field & field)
{
    _fields.emplace_back(field);
}

void d2o_class_definition::write(d2o_writer * owner, byte_buffer & buffer,
                                 const data_fields & fields) const
{
    for (auto && it : _fields)
        it.write(owner, buffer, fields.at(it.name()));
}

void d2o_class_definition::pack(byte_buffer & buffer, int id) const
{
    int count = _fields.size();
    buffer << id << _name << _package_name << count;
    for (auto && it : _fields)
        it.pack(buffer);
}
