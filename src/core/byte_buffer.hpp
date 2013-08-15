//
//  byte_buffer.hpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef core_byte_buffer_hpp
#define core_byte_buffer_hpp

#include <vector>
#include <fstream>
#include <string>
#include <type_traits>

void swap_bytes(uint8_t *, size_t);
void swap_bytes(uint8_t *, const uint8_t *, size_t);

enum class endianness
{
    LITTLE,
    BIG,
};


/*
 - class implementing primitive byte buffer manipulations
 - internal endianness: big endian
 */

class byte_buffer
{
private:
    size_t _rpos = 0, _wpos = 0;
    std::vector<uint8_t> _data;

public:
    static endianness ENDIANNESS;

    byte_buffer();
    explicit byte_buffer(std::vector<uint8_t>);
    explicit byte_buffer(std::ifstream &);
    
    void write_bytes(const uint8_t *, size_t);
    void clear();
    uint8_t & operator [](size_t);
    const uint8_t & operator [](size_t) const;

    template<class T>
    void write(const T & value)
    {
        static_assert(std::is_arithmetic<T>::value, "read requires arithmetic type");
        constexpr auto size = sizeof(T);
        if (size > 1 && byte_buffer::ENDIANNESS == endianness::LITTLE)
        {
            uint8_t raw[size];
            swap_bytes(raw, (const uint8_t*)&value, size);
            write_bytes(raw, size);
        }
        else
            write_bytes((const uint8_t*)&value, size);
    }

    template<class T>
    void read(T & value)
    {
        read<T>(_rpos, value);
        if (byte_buffer::ENDIANNESS == endianness::LITTLE)
            swap_bytes((uint8_t*)&value, sizeof(T));
        _rpos += sizeof(T);
    }

    template<class T>
    void read(size_t pos, T & value)
    {
        static_assert(std::is_arithmetic<T>::value, "read requires arithmetic type");
        auto size = sizeof(T);
        value = (pos + size <= _data.size() ? *((T*)&_data[pos]) : 0);
    }

    template<class T>
    void read_bytes(T & bytes, size_t count)
    {
        bytes.clear();
        if (count == 0)
            return;
        if (_rpos + count <= _data.size())
        {
            bytes.resize(count);
            memcpy((uint8_t*)&bytes[0], &_data[_rpos], count);
        }
        _rpos += count;
    }

    size_t tellg() const
    { return _rpos; }

    size_t tellp() const
    { return _wpos; }

    void seekg(size_t pos)
    { _rpos = pos; }

    void seekp(size_t pos)
    { _wpos = pos; }

    size_t size() const
    { return _data.size(); }

    const uint8_t * data() const
    { return _data.data(); }
};


/* write helpers */

template<class T>
byte_buffer & operator <<(byte_buffer & b, const T & v)
{
    b.write(v);
    return b;
}

template<>
byte_buffer & operator <<(byte_buffer &, const std::string &);

template<>
byte_buffer & operator <<(byte_buffer &, const std::vector<uint8_t> &);
template<>
byte_buffer & operator <<(byte_buffer &, const std::vector<int8_t> &);

template<>
byte_buffer & operator <<(byte_buffer &, const byte_buffer &);

/* read helpers */

template<class T>
byte_buffer & operator >>(byte_buffer & b, T & v)
{
    b.read(v);
    return b;
}

template<>
byte_buffer & operator >>(byte_buffer &, std::string &);

template<>
byte_buffer & operator >>(byte_buffer &, std::vector<uint8_t> &);
template<>
byte_buffer & operator >>(byte_buffer &, std::vector<int8_t> &);

#endif
