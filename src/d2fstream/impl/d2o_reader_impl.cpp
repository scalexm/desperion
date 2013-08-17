//
//  d2o_reader_impl.cpp
//  d2fstream
//
//  Created by Alexandre Martin on 31/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "../../core/common.hpp"
#include "d2o_reader_impl.hpp"

d2o_reader::impl::impl(std::ifstream & file, d2o_reader * owner) : _buffer { file },
    _owner { owner }
{
    std::string header(3, ' ');
    _buffer.read_bytes<false>(reinterpret_cast<uint8_t *>(&header[0]), 3);
    int beg = 0;
    if (header != "D2O")
    {
        _buffer.seekg(0);
        _buffer >> header;
        if (header != "D2OS")
            throw std::runtime_error { "corrupted d2o file "};
        int16_t unk;
        int offset;
        _buffer >> unk >> offset;
        _buffer.seekg(_buffer.tellg() + offset);
        beg = _buffer.tellg();
        _buffer.read_bytes<false>(reinterpret_cast<uint8_t *>(&header[0]), 3);
        if (header != "D2O")
            throw std::runtime_error { "corrupted d2os file "};
    }
    int offset;
    _buffer >> offset;
    _buffer.seekg(offset + beg);

    int size;
    _buffer >> size;
    for (auto a = 0; a < size; a += 8)
    {
        int index, value;
        _buffer >> index >> value;
        _objects.emplace(index, beg + value);
    }

    _buffer >> size;
    for (auto a = 0; a < size; ++a)
    {
        int class_id;
        std::string class_name, package_name;
        _buffer >> class_id >> class_name >> package_name;
        _classes.emplace(std::piecewise_construct,
                         std::forward_as_tuple(class_id),
                         std::forward_as_tuple(class_name, package_name, _buffer));
    }
}

const d2o_class_definition & d2o_reader::impl::get_class_definition(int class_id) const
{
    return _classes.at(class_id);
}

bool d2o_reader::impl::has_class_definition(int class_id) const
{
    return _classes.find(class_id) != end(_classes);
}

data_object d2o_reader::impl::read(int offset)
{
    _buffer.seekg(offset);
    int class_id;
    _buffer >> class_id;
    return { class_id, _classes.at(class_id).read(_owner, _buffer) };
}

data_object d2o_reader::impl::read_object(int index)
{
    return read(_objects.at(index));
}

std::unordered_map<int, data_object> d2o_reader::impl::read_all_objects()
{
    std::unordered_map<int, data_object> objects;
    for (auto && it : _objects)
        objects.emplace(it.first, read(it.second));
    return objects;
}
