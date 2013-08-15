//
//  data_holder.hpp
//  d2fstream
//
//  Created by Alexandre Martin on 31/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef d2fstream_data_holder_hpp
#define d2fstream_data_holder_hpp

#include <boost/any.hpp>
#include <vector>

class d2o_writer;

using data_fields = std::unordered_map<std::string, boost::any>;
using data_object = std::pair<int, data_fields>;

class data_holder
{
protected:
    data_holder() = default;

    template<class T>
    void acquire(std::vector<T> & val, boost::any & obj)
    {
        auto && vec = boost::any_cast<std::vector<boost::any>>(obj);
        val.resize(vec.size());
        for (size_t a = 0; a < vec.size(); ++a)
            acquire(val[a], vec[a]);
    }

    template<class T>
    typename std::enable_if<!std::is_base_of<data_holder, T>::value, void>::type
    acquire(T & val, boost::any & obj)
    { val = boost::any_cast<T>(obj); }

    template<class T>
    typename std::enable_if<std::is_base_of<data_holder, T>::value, void>::type
    acquire(T & val, boost::any & obj)
    {  val = boost::any_cast<data_object>(obj); }

    template<class T>
    void release(std::vector<T> & val, boost::any & obj, const d2o_writer & file)
    {
        std::vector<boost::any> vec(val.size());
        for (size_t a = 0; a < val.size(); ++a)
            release(val[a], vec[a], file);
        obj = std::move(vec);
    }

    template<class T>
    typename std::enable_if<!std::is_base_of<data_holder, T>::value, void>::type
    release(T & val, boost::any & obj, const d2o_writer &)
    { obj = std::move(val); }

    template<class T>
    typename std::enable_if<std::is_base_of<data_holder, T>::value, void>::type
    release(T & val, boost::any & obj, const d2o_writer & file)
    { obj = val.to_d2o(file); }
};

#endif
