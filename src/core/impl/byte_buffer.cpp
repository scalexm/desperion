//
//  byte_buffer.cpp
//  core
//
//  Created by Alexandre Martin on 17/08/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#include "../common.hpp"
#include "byte_buffer.hpp"

void reverse_bytes(uint8_t * bytes, size_t count)
{
    for (size_t lo = 0, hi = count - 1; hi > lo; ++lo, --hi)
    {
        auto temp = bytes[hi];
        bytes[hi] = bytes[lo];
        bytes[lo] = temp;
    }
}


byte_buffer::byte_buffer(std::vector<uint8_t> data) : _data { std::move(data) }
{
}

byte_buffer::byte_buffer(std::ifstream && file) : byte_buffer { file }
{

}

byte_buffer::byte_buffer(std::ifstream & file)
{
    if (!file)
        throw std::runtime_error { "bad file" };
    file.seekg(0, std::ifstream::end);
    size_t size = file.tellg();
    if(size != 0)
    {
        file.seekg(0, std::ifstream::beg);
        _data.resize(size + 1);
        file.read(reinterpret_cast<char *>(&_data[0]), size);
        _wpos = size + 1;
    }
}

bool empty(const byte_buffer & buffer)
{
    return buffer.size() == 0;
}

const uint8_t * data(const byte_buffer & buffer)
{
    return empty(buffer) ? nullptr : &buffer[0];
}

template<>
byte_buffer & operator <<(byte_buffer & buffer, const byte_buffer & val)
{
    buffer.write_bytes<false>(&val[0], val.size());
    return buffer;
}