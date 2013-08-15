//
//  sql_field.hpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef core_sql_field_hpp
#define core_sql_field_hpp

#include <boost/lexical_cast.hpp>

class sql_field
{
public:
    sql_field() = default;

    explicit sql_field(char * value) : _value { value }
    {
    }

    template<class T> T get() const
    { return boost::lexical_cast<T>(_value); }

private:
    char * _value = nullptr;
};


/*
 int8_t/uint8_t are aliases to respectively signed char/unsigned char,
 so we must use an intermediate integral conversion
*/

template<> inline uint8_t sql_field::get() const
{ return static_cast<uint8_t>(boost::lexical_cast<uint16_t>(_value)); }

template<> inline int8_t sql_field::get() const
{ return static_cast<int8_t>(boost::lexical_cast<int16_t>(_value)); }

#endif
