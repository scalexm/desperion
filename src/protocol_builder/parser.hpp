//
//  parser.hpp
//  protocol_builder
//
//  Created by Alexandre Martin on 05/08/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#ifndef protocol_builder_parser_hpp
#define protocol_builder_parser_hpp

#include <regex>
#include <string>
#include <fstream>

class parser
{
protected:
    std::string _content;
    std::string _class_name;
    std::string _inheritance;

private:
    std::string get_class_name() const;
    std::string get_inheritance() const;

public:
    parser(std::ifstream &);
    parser(std::ifstream &&);
    parser(std::string);

    virtual const std::string & class_name() const
    { return _class_name; }

    virtual const std::string & inheritance() const
    { return _inheritance; }

    virtual void parse() = 0;
};

#endif
