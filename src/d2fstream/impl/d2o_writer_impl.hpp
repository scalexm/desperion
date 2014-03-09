//
//  d2o_writer_impl.hpp
//  d2fstream
//
//  Created by Alexandre Martin on 31/07/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#ifndef d2fstream_d2o_writer_impl_hpp
#define d2fstream_d2o_writer_impl_hpp

#include "../d2o_writer.hpp"
#include "../../core/pimpl_impl.hpp"
#include "../d2o_class_definition.hpp"

class d2o_writer::impl
{
private:
    std::unordered_map<int, data_object> _objects;
    std::unordered_map<int, d2o_class_definition> _classes;
    d2o_writer * _owner;

public:
    impl(d2o_writer *);

    void add_class_definition(int, const d2o_class_definition &);
    void add_object(int, data_object &&);
    int get_class_id_for_hash(size_t) const;

    const d2o_class_definition & get_class_definition(int) const;
    bool has_class_definition(int) const;

    void write(std::ofstream &) const;
};

#endif
