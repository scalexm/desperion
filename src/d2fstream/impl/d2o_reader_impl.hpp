//
//  d2o_reader_impl.hpp
//  d2fstream
//
//  Created by Alexandre Martin on 31/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef d2fstream_d2o_reader_impl_hpp
#define d2fstream_d2o_reader_impl_hpp

#include "../d2o_reader.hpp"
#include "../../core/pimpl_impl.hpp"
#include "../d2o_class_definition.hpp"
#include "../../core/byte_buffer.hpp"

class d2o_reader::impl
{
private:
    std::unordered_map<int, int> _objects;
    std::unordered_map<int, d2o_class_definition> _classes;
    byte_buffer _buffer;
    d2o_reader * _owner;

    data_object read(int);
public:
    impl(std::ifstream &, d2o_reader *);

    data_object read_object(int);
    std::unordered_map<int, data_object> read_all_objects();

    const d2o_class_definition & get_class_definition(int) const;
    bool has_class_definition(int) const;
};

#endif
