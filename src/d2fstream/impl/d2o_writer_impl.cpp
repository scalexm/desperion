//
//  d2o_writer_impl.cpp
//  d2fstream
//
//  Created by Alexandre Martin on 31/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "../../core/common.hpp"
#include "d2o_writer_impl.hpp"
#include "../../core/byte_buffer.hpp"

d2o_writer::impl::impl(d2o_writer * owner) : _owner { owner }
{
}

void d2o_writer::impl::add_class_definition(int id, const d2o_class_definition & c)
{
    _classes.emplace(id, c);
}

void d2o_writer::impl::add_object(int id, data_object && obj)
{
    _objects.emplace(id, std::move(obj));
}

int d2o_writer::impl::get_class_id_for_hash(size_t hash) const
{
    for (auto && it : _classes)
        if (it.second.cpp_hash() == hash)
            return it.first;
    throw std::runtime_error { "no d2o_class_definition bound" };
}

const d2o_class_definition & d2o_writer::impl::get_class_definition(int id) const
{
    return _classes.at(id);
}

bool d2o_writer::impl::has_class_definition(int id) const
{
    return _classes.find(id) != end(_classes);
}

void d2o_writer::impl::write(std::ofstream & file) const
{
    byte_buffer buffer;
    buffer.write_bytes<false>((const uint8_t *)"D2O", 3);
    buffer << 0;
    std::unordered_map<int, int> offsets;
    for (auto && it : _objects)
    {
        offsets.emplace(it.first, buffer.tellp());
        buffer << it.second.first;
        _classes.at(it.second.first).write(_owner, buffer, it.second.second);
    }

    int header = buffer.tellp();

    buffer << static_cast<int>(offsets.size() * 8);
    for (auto && it : offsets)
        buffer << it.first << it.second;
    buffer << static_cast<int>(_classes.size());
    for (auto && it : _classes)
        it.second.pack(buffer, it.first);

    buffer.seekp(3);
    buffer << header;
    file.write((const char *)&buffer[0], buffer.size());
}
