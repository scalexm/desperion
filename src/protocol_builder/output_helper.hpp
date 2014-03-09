//
//  output_helper.hpp
//  protocol_builder
//
//  Created by Alexandre Martin on 06/08/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#ifndef protocol_builder_output_helper_hpp
#define protocol_builder_output_helper_hpp

#include <sstream>
#include <string>
#include <cassert>

inline std::string to_cpp_case(const std::string & str)
{
    std::string result;
    for (auto i = 0; i < str.size(); ++i)
    {
        if (i != 0 && std::toupper(str[i]) == str[i])
            result += "_";
        result += std::tolower(str[i]);
    }
    return result;
}

class output
{
private:
    std::ostringstream _content;
    int _indent_level = 0;

public:
    output() = default;

    output & indent()
    {
        ++_indent_level;
        return *this;
    }

    output & unindent()
    {
        --_indent_level;
        assert( _indent_level >= 0 );
        return *this;
    }

    output & next(bool indent = true)
    {
        _content << std::endl;
        if (indent && _indent_level != 0)
        {
            // parenthesis are important here because of std::string initializer_list ctor
            _content << std::string(4 * _indent_level, ' ');
        }
        return *this;
    }

    template<class T>
    output & operator <<(const T & val)
    {
        _content << val;
        return *this;
    }

    std::string str() const
    { return _content.str(); }
};

#endif
