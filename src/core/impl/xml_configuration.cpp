//
//  xml_configuration.cpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "../common.hpp"
#include "../xml_configuration.hpp"
#include "third_party/pugixml.hpp"
#include <iostream>

/* uses pugixml library: pugiconfig.hpp/pugixml.hpp/pugixml.cpp */

xml_configuration::xml_configuration(std::list<std::string> files) : _files { std::move(files) }
{
    parse_all();
}

void xml_configuration::parse_all()
{
    for (auto && file : _files)
    {
        auto result = parse_file(file);
        if (!result.empty()) // no need to throw because desperion has default values for config options
            std::cerr << "parsing failed " << file << ": " << result << std::endl;
    }
}

std::string xml_configuration::parse_file(const std::string & filename)
{
    pugi::xml_document doc;
    auto res = doc.load_file(filename.c_str());
    if (!res)
        return boost::lexical_cast<std::string>(res.offset) + " " + res.description();
    for (auto && it : doc.child("config"))
        _properties.emplace(it.name(), it.child_value());
    return { };
}

template<> bool xml_configuration::get_property(const std::string & index, const bool & def)
{
    auto it = _properties.find(boost::algorithm::to_lower_copy(index));
    if (it == end(_properties))
        return def;
    return boost::algorithm::to_lower_copy(it->second) != "false";
}

template<> std::string xml_configuration::get_property(const std::string & index,
                                                       const std::string & def)
{
    auto it = _properties.find(boost::algorithm::to_lower_copy(index));
    if (it == end(_properties))
        return def;
    return it->second;
}