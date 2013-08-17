//
//  byte_buffer.hpp
//  Test
//
//  Created by Alexandre Martin on 17/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef core_byte_buffer_hpp
#define core_byte_buffer_hpp

#include <vector>
#include <type_traits>
#include <fstream>
#include <boost/detail/endian.hpp>

void reverse_bytes(uint8_t *, size_t);

namespace policies
{
    template<bool>
    struct endianness;

    template<>
    struct endianness<true>
    {
        static void apply(uint8_t * bytes, size_t count)
        {
            reverse_bytes(bytes, count);
        }
    };

    template<>
    struct endianness<false>
    {
        static void apply(uint8_t * bytes, size_t count)
        {
        }
    };
}

class byte_buffer
{
private:
    std::vector<uint8_t> _data;
    size_t _wpos = 0, _rpos = 0;

public:
    byte_buffer() = default;
    explicit byte_buffer(std::vector<uint8_t>);
    explicit byte_buffer(std::ifstream &&);
    explicit byte_buffer(std::ifstream &);

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

    void clear()
    { _data.clear(); }

    uint8_t & operator [](size_t pos)
    { return _data[pos]; }

    const uint8_t & operator [](size_t pos) const
    { return _data[pos]; }

    template<bool Apply>
    void write_bytes(const uint8_t * bytes, size_t count)
    {
        if (bytes == nullptr || count == 0)
            return;
        if (_data.size() < _wpos + count)
            _data.resize(_wpos + count);
        memcpy(&_data[_wpos], bytes, count);
#ifdef BOOST_LITTLE_ENDIAN
        policies::endianness<Apply>::apply(&_data[_wpos], count);
#endif
        _wpos += count;
    }

    template<bool Apply>
    void read_bytes(uint8_t * bytes, size_t count)
    {
        if (bytes == nullptr || count == 0)
            return;
        if (_rpos + count <= size())
            memcpy(bytes, &_data[_rpos], count);
#ifdef BOOST_LITTLE_ENDIAN
        policies::endianness<Apply>::apply(bytes, count);
#endif
        _rpos += count;
    }
};

template<class T>
inline void write(byte_buffer & buffer, const T & value)
{
    static_assert(std::is_trivially_copyable<T>::value, "write requires trivially copyable type");
    buffer.write_bytes<true>(reinterpret_cast<const uint8_t *>(&value), sizeof(T));
}

template<class T>
inline void read(byte_buffer & buffer, T & value)
{
    static_assert(std::is_trivially_copyable<T>::value, "read requires trivially copyable type");
    buffer.read_bytes<true>(reinterpret_cast<uint8_t *>(&value), sizeof(T));
}

template<class T>
inline typename std::enable_if<std::is_trivially_copyable<T>::value,
    byte_buffer &>::type
operator <<(byte_buffer & buffer, const T & val)
{
    write(buffer, val);
    return buffer;
}

template<class T>
inline typename std::enable_if<!std::is_void<decltype(std::declval<T>().size())>::value,
    byte_buffer &>::type
operator <<(byte_buffer & buffer, const T & val)
{
    uint16_t size = static_cast<uint16_t>(val.size());
    write(buffer, size);
    buffer.write_bytes<false>(reinterpret_cast<const uint8_t *>(&val[0]), size);
    return buffer;
}

template<class T>
inline typename std::enable_if<std::is_trivially_copyable<T>::value,
    byte_buffer &>::type
operator >>(byte_buffer & buffer, T & val)
{
    read(buffer, val);
    return buffer;
}

template<class T>
inline typename std::enable_if<!std::is_void<decltype(std::declval<T>().size())>::value,
    byte_buffer &>::type
operator >>(byte_buffer & buffer, T & val)
{
    uint16_t size;
    read(buffer, size);
    val.resize(size);
    buffer.read_bytes<false>(reinterpret_cast<uint8_t *>(&val[0]), size);
    return buffer;
}

bool empty(const byte_buffer &);
const uint8_t * data(const byte_buffer &);
template<>
byte_buffer & operator <<(byte_buffer &, const byte_buffer &);

#endif