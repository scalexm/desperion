//
//  d2o_reader.hpp
//  d2fstream
//
//  Created by Alexandre Martin on 31/07/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#ifndef d2fstream_d2o_reader_hpp
#define d2fstream_d2o_reader_hpp

#include "../core/pimpl.hpp"
#include <unordered_map>
#include <string>
#include <fstream>
#include <list>

class d2o_class_definition;
using void_ptr = std::unique_ptr<void>;
using data_fields = std::list<void_ptr>;
//using data_fields = std::unordered_map<std::string, void_ptr>;
using data_object = std::pair<int, data_fields>;

class d2o_reader
{
private:
    class impl;
    pimpl<impl> _impl;

public:
    d2o_reader(std::ifstream &);
    d2o_reader(std::ifstream &&);
    ~d2o_reader();

    data_object read_object(int);
    std::unordered_map<int, data_object> read_all_objects();

    const d2o_class_definition & get_class_definition(int) const;
    bool has_class_definition(int) const;
};

#endif
