//
//  d2i_reader_impl.cpp
//  d2fstream
//
//  Created by Alexandre Martin on 31/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "../../core/common.hpp"
#include "d2i_reader_impl.hpp"

d2i_reader::impl::impl(std::ifstream & file) : _buffer { file }
{
    int offset;
    _buffer >> offset;
    _buffer.seekg(offset);

    int size, iter = 0;
    _buffer >> size;
    while (iter < size)
    {
        int index, value;
        bool b;
        _buffer >> index >> b >> value;
        _texts.emplace(index, value);
        if (b)
        {
            iter += 4;
            _buffer >> value;
        }
        iter += 9;
    }

    _buffer >> size;
    while (size > 0)
    {
        std::string index;
        int pos = _buffer.tellg(), value;
        _buffer >> index >> value;
        _ui_texts.emplace(std::move(index), value);
        size -= _buffer.tellg() - pos;
    }
}

std::string d2i_reader::impl::read(int offset)
{
    _buffer.seekg(offset);
    std::string value;
    _buffer >> value;
    return value;
}

std::string d2i_reader::impl::read_text(int index)
{
    return read(_texts.at(index));
}

std::string d2i_reader::impl::read_ui_text(const std::string& index)
{
    return read(_ui_texts.at(index));
}

std::unordered_map<int, std::string> d2i_reader::impl::read_all_text()
{
    std::unordered_map<int, std::string> map;
    for (auto && it : _texts)
        map.emplace(it.first, read(it.second));
    return map;
}

std::unordered_map<std::string, std::string> d2i_reader::impl::read_all_ui_text()
{
    std::unordered_map<std::string, std::string> map;
    for (auto && it : _ui_texts)
        map.emplace(it.first, read(it.second));
    return map;
}

bool d2i_reader::impl::has_text(int index) const
{
    return _texts.find(index) != end(_texts);
}

bool d2i_reader::impl::has_ui_text(const std::string & index) const
{
    return _ui_texts.find(index) != end(_ui_texts);
}