//
//  d2o_writer.hpp
//  d2fstream
//
//  Created by Alexandre Martin on 31/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef d2fstream_d2o_writer_hpp
#define d2fstream_d2o_writer_hpp

#include "../core/pimpl.hpp"
#include <unordered_map>
#include <boost/any.hpp>
#include <string>

class d2o_class_definition;
using data_fields = std::unordered_map<std::string, boost::any>;
using data_object = std::pair<int, data_fields>;

class d2o_writer
{
private:
    class impl;
    pimpl<impl> _impl;

    int get_class_id_for_hash(size_t) const;
public:
    d2o_writer();
    ~d2o_writer();

    void add_class_definition(int, const d2o_class_definition &);
    void add_object(int, const data_object &);
    void add_object(int, data_object &&);

    template<class T>
    int get_class_id_for_type() const
    { return get_class_id_for_hash(typeid(T).hash_code()); }

    const d2o_class_definition & get_class_definition(int) const;
    bool has_class_definition(int) const;

    void write(std::ofstream &) const;
    void write(std::ofstream &&) const;
};


#endif
