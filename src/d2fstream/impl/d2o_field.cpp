//
//  d2o_field.cpp
//  d2fstream
//
//  Created by Alexandre Martin on 31/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "../../core/common.hpp"
#include "../d2o_field.hpp"
#include "../../core/byte_buffer.hpp"
#include "../d2o_reader.hpp"
#include "../d2o_writer.hpp"
#include "../d2o_class_definition.hpp"
#include <cassert>

d2o_field::d2o_field(std::string name, int type, type_vector vec_types)
    : _name { std::move(name) }, _type { type }, _vector_types { std::move(vec_types) }
{
}

d2o_field::d2o_field(std::string name, int type, byte_buffer & buffer)
    : _type { type }, _name { std::move(name) }
{
    while (type == -99)
    {
        std::string str;
        buffer >> str >> type;
        _vector_types.emplace_back(str, type);
    }
}

auto d2o_field::get_read_method(int type) const -> read_method
{
    switch (type)
    {
        case D2O_FIELD_TYPE_INT:
            return &d2o_field::read_int;
        case D2O_FIELD_TYPE_BOOL:
            return &d2o_field::read_bool;
        case D2O_FIELD_TYPE_STRING:
            return &d2o_field::read_string;
        case D2O_FIELD_TYPE_NUMBER:
            return &d2o_field::read_number;
        case D2O_FIELD_TYPE_I18N:
            return &d2o_field::read_int;
        case D2O_FIELD_TYPE_UINT:
            return &d2o_field::read_uint;
        case D2O_FIELD_TYPE_VECTOR:
            return &d2o_field::read_vector;
        default:
            return &d2o_field::read_object;
    }
}

auto d2o_field::get_write_method(int type) const -> write_method
{
    switch (type)
    {
        case D2O_FIELD_TYPE_INT:
            return &d2o_field::write_int;
        case D2O_FIELD_TYPE_BOOL:
            return &d2o_field::write_bool;
        case D2O_FIELD_TYPE_STRING:
            return &d2o_field::write_string;
        case D2O_FIELD_TYPE_NUMBER:
            return &d2o_field::write_number;
        case D2O_FIELD_TYPE_I18N:
            return &d2o_field::write_int;
        case D2O_FIELD_TYPE_UINT:
            return &d2o_field::write_uint;
        case D2O_FIELD_TYPE_VECTOR:
            return &d2o_field::write_vector;
        default:
            return &d2o_field::write_object;
    }
}


/* not very pretty, but can't find an other way to do it */

boost::any d2o_field::read(d2o_reader * owner, byte_buffer & buffer) const
{
    assert( owner );
    return (this->*get_read_method(_type))(owner, buffer, 0);
}

boost::any d2o_field::read_object(d2o_reader * owner, byte_buffer & buffer, int) const
{
    int class_id;
    buffer >> class_id;
    return {
        data_object {
            class_id,
            class_id >= 0 ? owner->get_class_definition(class_id).read(owner, buffer)
                : data_fields { }
        }
    };
}

boost::any d2o_field::read_vector(d2o_reader * owner, byte_buffer & buffer, int dim) const
{
    int count;
    buffer >> count;
    std::vector<boost::any> result;
    for (auto a = 0; a < count; ++a)
    {
        result.push_back((this->*get_read_method(_vector_types[dim].second))(owner,
                                                                             buffer,
                                                                             dim + 1));
    }
    return { std::move(result) };
}

boost::any d2o_field::read_int(d2o_reader *, byte_buffer & buffer, int) const
{
    int i;
    buffer >> i;
    return { i };
}

boost::any d2o_field::read_bool(d2o_reader *, byte_buffer & buffer, int) const
{
    bool b;
    buffer >> b;
    return { b };
}

boost::any d2o_field::read_string(d2o_reader *, byte_buffer & buffer, int) const
{
    std::string s;
    buffer >> s;
    return { std::move(s) };
}

boost::any d2o_field::read_number(d2o_reader *, byte_buffer & buffer, int) const
{
    double d;
    buffer >> d;
    return { d };
}

boost::any d2o_field::read_uint(d2o_reader *, byte_buffer & buffer, int) const
{
    uint32_t u;
    buffer >> u;
    return { u };
}

void d2o_field::write(d2o_writer * owner, byte_buffer & buffer,
                      const boost::any & field) const
{
    assert( owner );
    (this->*get_write_method(_type))(owner, buffer, field, 0);
}

void d2o_field::write_object(d2o_writer * owner, byte_buffer & buffer,
                             const boost::any & field,
                             int) const
{
    auto && obj = boost::any_cast<data_object>(field);
    buffer << obj.first;
    owner->get_class_definition(obj.first).write(owner, buffer, obj.second);
}

void d2o_field::write_vector(d2o_writer * owner, byte_buffer & buffer,
                             const boost::any & field,
                             int dim) const
{
    auto && vec = boost::any_cast<std::vector<boost::any>>(field);
    int count = vec.size();
    buffer << count;
    for (auto a = 0; a < count; ++a)
        (this->*get_write_method(_vector_types[dim].second))(owner, buffer, vec[a], dim + 1);
}

void d2o_field::write_int(d2o_writer *, byte_buffer & buffer, const boost::any & field,
                          int) const
{
    buffer << boost::any_cast<int>(field);
}

void d2o_field::write_bool(d2o_writer *, byte_buffer & buffer, const boost::any & field,
                           int) const
{
    buffer << boost::any_cast<bool>(field);
}

void d2o_field::write_string(d2o_writer *, byte_buffer & buffer, const boost::any & field,
                             int) const
{
    buffer << boost::any_cast<std::string>(field);
}

void d2o_field::write_number(d2o_writer *, byte_buffer & buffer, const boost::any & field,
                             int) const
{
    buffer << boost::any_cast<double>(field);
}

void d2o_field::write_uint(d2o_writer *, byte_buffer & buffer, const boost::any & field,
                           int) const
{
    buffer << boost::any_cast<uint32_t>(field);
}

void d2o_field::pack(byte_buffer & buffer) const
{
    buffer << _name << _type;
    if (_type == -99)
    {
        if (_vector_types.empty())
            throw std::runtime_error { "empty type vector" };
        for (auto && t : _vector_types)
            buffer << t.first << t.second;
    }
}
