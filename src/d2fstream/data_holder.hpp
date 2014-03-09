//
//  data_holder.hpp
//  d2fstream
//
//  Created by Alexandre Martin on 31/07/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#ifndef d2fstream_data_holder_hpp
#define d2fstream_data_holder_hpp

#include <vector>
#include <unordered_map>

class d2o_writer;

using void_ptr = std::unique_ptr<void>;
using data_fields = std::unordered_map<std::string, void_ptr>;
using data_object = std::pair<int, data_fields>;

class data_holder
{
protected:
    data_holder() = default;

    template<class T>
    void acquire(std::vector<T> & val, void_ptr & obj)
    {
        auto vec = static_cast<std::vector<void_ptr>*>(obj.get());
        val.resize(vec->size());
        for (size_t a = 0; a < vec->size(); ++a)
            acquire(val[a], (*vec)[a]);
    }

    template<class T>
    typename std::enable_if<!std::is_base_of<data_holder, T>::value, void>::type
    acquire(T & val, void_ptr & obj)
    { val = std::move(*static_cast<T*>(obj.get())); }

    template<class T>
    typename std::enable_if<std::is_base_of<data_holder, T>::value, void>::type
    acquire(T & val, void_ptr & obj)
    {  val = std::move(*static_cast<data_object*>(obj.get())); }

    template<class T>
    void release(std::vector<T> & val, void_ptr & obj, const d2o_writer & file)
    {
        std::vector<void_ptr> vec(val.size());
        for (size_t a = 0; a < val.size(); ++a)
            release(val[a], vec[a], file);
        obj = std::make_unique<std::vector<void_ptr>>(std::move(vec));
    }

    template<class T>
    typename std::enable_if<!std::is_base_of<data_holder, T>::value, void>::type
    release(T & val, void_ptr & obj, const d2o_writer &)
    { obj = std::make_unique<T>(std::move(val)); }

    template<class T>
    typename std::enable_if<std::is_base_of<data_holder, T>::value, void>::type
    release(T & val, void_ptr & obj, const d2o_writer & file)
    { obj = std::make_unique<data_object>(val.to_d2o(file)); }
};

#endif
