//
//  byte_buffer.cpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "../common.hpp"
#include "../byte_buffer.hpp"

void swap_bytes(uint8_t * p, size_t n)
{
    size_t lo, hi;
    for (lo = 0, hi = n - 1; hi > lo; lo++, hi--)
    {
        auto temp = p[hi];
        p[hi] = p[lo];
        p[lo] = temp;
    }
}

void swap_bytes(uint8_t * p, const uint8_t * r, size_t n)
{
    size_t lo, hi;
    for (lo = 0, hi = n - 1; hi > lo; lo++, hi--)
    {
        p[hi] = r[lo];
        p[lo] = r[hi];
    }
}

namespace
{
    endianness get_endianness()
    {
        union
        {
            int i;
            char c[sizeof(int)];
        } x;
        x.i = 1;
        if (x.c[0] == 1)
            return endianness::LITTLE;
        else
            return endianness::BIG;
    }
}

endianness byte_buffer::ENDIANNESS = get_endianness(); // endianness at runtime

byte_buffer::byte_buffer()
{
    _data.reserve(100);
}

byte_buffer::byte_buffer(std::vector<uint8_t> data) : _data { std::move(data) }
{
    
}

byte_buffer::byte_buffer(std::ifstream & file)
{
    if (!file)
        throw std::runtime_error { "bad file" };
    file.seekg(0, std::ifstream::end);
    size_t size = file.tellg();
    if(size == 0)
        return;
    file.seekg(0, std::ifstream::beg);
    _data.resize(size + 1);
    file.read((char *)&_data[0], size);
    _wpos = size + 1;
}

void byte_buffer::write_bytes(const uint8_t * bytes, size_t count)
{
    if (bytes == nullptr || count == 0)
        return;
    if (_data.size() < _wpos + count)
        _data.resize(_wpos + count);
    memcpy(&_data[_wpos], bytes, count);
    _wpos += count;
}

void byte_buffer::clear()
{
    _data.clear();
    _rpos = _wpos = 0;
}

uint8_t & byte_buffer::operator [](size_t pos)
{
    return _data[pos];
}

const uint8_t & byte_buffer::operator [](size_t pos) const
{
    return _data[pos];
}

namespace
{
    template<class T>
    void write_bytes(byte_buffer & b, const T & v)
    {
        uint16_t size = v.size();
        b.write(size);
        b.write_bytes((uint8_t*)&v[0], size);
    }

    template<class T>
    void read_bytes(byte_buffer & b, T & v)
    {
        uint16_t size;
        b.read(size);
        b.read_bytes(v, size);
    }
}


/* writing stuff */

template<>
byte_buffer & operator <<(byte_buffer & b, const std::string & v)
{
    write_bytes(b, v);
    return b;
}

template<>
byte_buffer & operator <<(byte_buffer & b, const std::vector<uint8_t> & v)
{
    write_bytes(b, v);
    return b;
}

template<>
byte_buffer & operator <<(byte_buffer & b, const std::vector<int8_t> & v)
{
    write_bytes(b, v);
    return b;
}

template<>
byte_buffer & operator <<(byte_buffer & b, const byte_buffer & v)
{
    auto size = v.size();
    b.write_bytes(v.data(), size);
    return b;
}


/* reading stuff */

template<>
byte_buffer & operator >>(byte_buffer & b, std::string & v)
{
    read_bytes(b, v);
    return b;
}

template<>
byte_buffer & operator >>(byte_buffer & b, std::vector<uint8_t> & v)
{
    read_bytes(b, v);
    return b;
}

template<>
byte_buffer & operator >>(byte_buffer & b, std::vector<int8_t> & v)
{
    read_bytes(b, v);
    return b;
}