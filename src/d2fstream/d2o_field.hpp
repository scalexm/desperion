//
//  d2o_field.hpp
//  d2fstream
//
//  Created by Alexandre Martin on 31/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef d2fstream_d2o_field_hpp
#define d2fstream_d2o_field_hpp

#include <vector>
#include <unordered_map>
#include <string>
#include <boost/any.hpp>

class byte_buffer;
class d2o_reader;
class d2o_writer;

enum d2o_field_type
{
    D2O_FIELD_TYPE_INT = -1,
    D2O_FIELD_TYPE_BOOL = -2,
    D2O_FIELD_TYPE_STRING = -3,
    D2O_FIELD_TYPE_NUMBER = -4,
    D2O_FIELD_TYPE_I18N = -5,
    D2O_FIELD_TYPE_UINT = -6,
    D2O_FIELD_TYPE_VECTOR = -99,
};

class d2o_field
{
public:
    using type_vector = std::vector<std::pair<std::string, int>>;
private:
    using read_method = boost::any(d2o_field::*)(d2o_reader *, byte_buffer &, int) const;
    using write_method = void(d2o_field::*)(d2o_writer *, byte_buffer &, const boost::any &,
                                            int) const;

    type_vector _vector_types;
    std::string _name;
    int _type;

    read_method get_read_method(int) const;
    write_method get_write_method(int) const;

    boost::any read_object(d2o_reader *, byte_buffer &, int) const;
    boost::any read_vector(d2o_reader *, byte_buffer &, int) const;
    boost::any read_int(d2o_reader *, byte_buffer &, int) const;
    boost::any read_bool(d2o_reader *, byte_buffer &, int) const;
    boost::any read_string(d2o_reader *, byte_buffer &, int) const;
    boost::any read_number(d2o_reader *, byte_buffer &, int) const;
    boost::any read_uint(d2o_reader *, byte_buffer &, int) const;

    void write_object(d2o_writer *, byte_buffer &, const boost::any &, int) const;
    void write_vector(d2o_writer *, byte_buffer &, const boost::any &, int) const;
    void write_int(d2o_writer *, byte_buffer &, const boost::any &, int) const;
    void write_bool(d2o_writer *, byte_buffer &, const boost::any &, int) const;
    void write_string(d2o_writer *, byte_buffer &, const boost::any &, int) const;
    void write_number(d2o_writer *, byte_buffer &, const boost::any &, int) const;
    void write_uint(d2o_writer *, byte_buffer &, const boost::any &, int) const;

public:
    d2o_field(std::string, int, type_vector);
    d2o_field(std::string, int, byte_buffer &);

    boost::any read(d2o_reader *, byte_buffer &) const;
    void write(d2o_writer *, byte_buffer &, const boost::any &) const;

    void pack(byte_buffer &) const;

    const std::string & name() const
    { return _name; }

    int type() const
    { return _type; }
};


#endif
