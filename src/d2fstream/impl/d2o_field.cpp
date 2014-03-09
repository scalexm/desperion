//
//  d2o_field.cpp
//  d2fstream
//
//  Created by Alexandre Martin on 31/07/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
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

void_ptr d2o_field::read(d2o_reader * owner, byte_buffer & buffer) const
{
    assert( owner );
    return (this->*get_read_method(_type))(owner, buffer, 0);
}

void_ptr d2o_field::read_object(d2o_reader * owner, byte_buffer & buffer, int) const
{
    int class_id;
    buffer >> class_id;
    return std::make_unique<data_object>(class_id,
                                         class_id >= 0 ?
                                            owner->get_class_definition(class_id).read(owner,
                                                                                       buffer)
                                            : data_fields { });
}

void_ptr d2o_field::read_vector(d2o_reader * owner, byte_buffer & buffer, int dim) const
{
    int count;
    buffer >> count;
    auto result = std::make_unique<std::vector<void_ptr>>();
    for (auto a = 0; a < count; ++a)
    {
        result->push_back((this->*get_read_method(_vector_types[dim].second))(owner,
                                                                              buffer,
                                                                              dim + 1));
    }
    return void_ptr { std::move(result) };
}

void_ptr d2o_field::read_int(d2o_reader *, byte_buffer & buffer, int) const
{
    int32_t i;
    buffer >> i;
    return std::make_unique<int32_t>(i);
}

void_ptr d2o_field::read_bool(d2o_reader *, byte_buffer & buffer, int) const
{
    bool b;
    buffer >> b;
    return std::make_unique<bool>(b);
}

void_ptr d2o_field::read_string(d2o_reader *, byte_buffer & buffer, int) const
{
    std::string s;
    buffer >> s;
    return std::make_unique<std::string>(std::move(s));
}

void_ptr d2o_field::read_number(d2o_reader *, byte_buffer & buffer, int) const
{
    double d;
    buffer >> d;
    return std::make_unique<double>(d);
}

void_ptr d2o_field::read_uint(d2o_reader *, byte_buffer & buffer, int) const
{
    uint32_t u;
    buffer >> u;
    return std::make_unique<uint32_t>(u);
}

void d2o_field::write(d2o_writer * owner, byte_buffer & buffer,
                      const void_ptr & field) const
{
    assert( owner );
    (this->*get_write_method(_type))(owner, buffer, field, 0);
}

void d2o_field::write_object(d2o_writer * owner, byte_buffer & buffer,
                             const void_ptr & field,
                             int) const
{
    auto obj = reinterpret_cast<data_object*>(field.get());
    buffer << obj->first;
    owner->get_class_definition(obj->first).write(owner, buffer, obj->second);
}

void d2o_field::write_vector(d2o_writer * owner, byte_buffer & buffer,
                             const void_ptr & field,
                             int dim) const
{
    auto vec = static_cast<std::vector<void_ptr>*>(field.get());
    int count = vec->size();
    buffer << count;
    for (auto a = 0; a < count; ++a)
        (this->*get_write_method(_vector_types[dim].second))(owner, buffer, (*vec)[a], dim + 1);
}

void d2o_field::write_int(d2o_writer *, byte_buffer & buffer, const void_ptr & field,
                          int) const
{
    buffer << *static_cast<int*>(field.get());
}

void d2o_field::write_bool(d2o_writer *, byte_buffer & buffer, const void_ptr & field,
                           int) const
{
    buffer << *static_cast<bool*>(field.get());
}

void d2o_field::write_string(d2o_writer *, byte_buffer & buffer, const void_ptr & field,
                             int) const
{
    buffer << *static_cast<std::string*>(field.get());
}

void d2o_field::write_number(d2o_writer *, byte_buffer & buffer, const void_ptr & field,
                             int) const
{
    buffer << *static_cast<double*>(field.get());
}

void d2o_field::write_uint(d2o_writer *, byte_buffer & buffer, const void_ptr & field,
                           int) const
{
    buffer << *static_cast<uint32_t*>(field.get());
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
