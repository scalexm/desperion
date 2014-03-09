//
//  parser.cpp
//  protocol_builder
//
//  Created by Alexandre Martin on 06/08/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#include "parser.hpp"
#include <regex>
#include <sstream>

parser::parser(std::ifstream & file)
{
    if (!file)
        throw std::runtime_error { "invalid file" };
    std::ostringstream ss;
    ss << file.rdbuf();
    _content = ss.str();
    _class_name = get_class_name();
    _inheritance = get_inheritance();
}

parser::parser(std::ifstream && file) : parser { file }
{

}

parser::parser(std::string content) : _content { std::move(content) }
{
    _class_name = get_class_name();
    _inheritance = get_inheritance();
}

std::string parser::get_class_name() const
{
    const std::regex pattern { R"(public class (\w+))" };
    std::smatch result;
    if (std::regex_search(_content, result, pattern))
        return result[1];
    throw std::runtime_error { "malformated file: can't find class name" };
}

std::string parser::get_inheritance() const
{
    const std::regex pattern { R"(extends (?:[\w_]+\.)*(\w+))" };
    std::smatch result;
    if (std::regex_search(_content, result, pattern))
        return result[1];
    throw std::runtime_error { "malformated file: can't find inheritance" };
}
