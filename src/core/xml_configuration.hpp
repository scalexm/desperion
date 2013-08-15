//
//  xml_configuration.hpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef core_xml_configuration_hpp
#define core_xml_configuration_hpp

#include <unordered_map>
#include <list>
#include <string>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

class xml_configuration
{
public:
    explicit xml_configuration(std::list<std::string>);
    void parse_all();

    template<class T>
    T get_property(const std::string & index, const T & def)
    {
        auto it = _properties.find(boost::algorithm::to_lower_copy(index));
        if (it != end(_properties))
            return boost::lexical_cast<T>(it->second);
        return def;
    }

    const std::unordered_map<std::string, std::string> & get_properties()
    { return _properties; }

private:
    std::list<std::string> _files;
    std::unordered_map<std::string, std::string> _properties;
    std::string parse_file(const std::string &);
};

template<> bool xml_configuration::get_property(const std::string &, const bool &);
template<> std::string xml_configuration::get_property(const std::string &, const std::string &);

#endif
