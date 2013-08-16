//
//  datacenter_file.hpp
//  protocol_builder
//
//  Created by Alexandre Martin on 16/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef protocol_builder_datacenter_file_hpp
#define protocol_builder_datacenter_file_hpp

#include "parser.hpp"
#include <list>
#include <string>
#include <unordered_map>

class datacenter_file : public parser
{
public:
    using field_list = std::list<std::pair<std::string, std::string>>;
private:
    field_list _fields;
public:
    using parser::parser;
    void parse() override;
    std::string cpp_output(const std::unordered_map<std::string, datacenter_file> &) const;

    const field_list & fields() const
    { return _fields; }

};

#endif
