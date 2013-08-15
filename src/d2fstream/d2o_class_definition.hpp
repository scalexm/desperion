//
//  d2o_class_definition.hpp
//  d2fstream
//
//  Created by Alexandre Martin on 31/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef d2fstream_d2o_class_definition_hpp
#define d2fstream_d2o_class_definition_hpp

#include "d2o_field.hpp"
#include <list>

using data_fields = std::unordered_map<std::string, boost::any>;

class d2o_class_definition
{
private:
    size_t _cpp_hash;
    std::string _name, _package_name;
    std::list<d2o_field> _fields;

public:
    d2o_class_definition(std::string, std::string);
    d2o_class_definition(std::string, std::string, byte_buffer &);
    data_fields read(d2o_reader *, byte_buffer &) const;
    void add_field(const d2o_field &);
    void write(d2o_writer *, byte_buffer &, const data_fields &) const;
    void pack(byte_buffer &, int) const;

    template<class T>
    void bind_cpp_type()
    { _cpp_hash = typeid(T).hash_code(); }

    size_t cpp_hash() const // for auto classdef id generating (see d2o file format)
    { return _cpp_hash; }

    const std::string & name() const
    { return _name; }

    const std::string & package_name() const
    { return _package_name; }

    const std::list<d2o_field> & fields() const
    { return _fields; }
};


#endif
