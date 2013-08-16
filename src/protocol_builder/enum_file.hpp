//
//  enum_file.hpp
//  protocol_builder
//
//  Created by Alexandre Martin on 05/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef protocol_builder_enum_file_hpp
#define protocol_builder_enum_file_hpp

#include "parser.hpp"
#include <list>

class enum_file : public parser
{
public:
    class constant
    {
    private:
        std::string _name;
        int _value;

    public:
        constant(std::string name, int value) : _name { std::move(name) }, _value { value }
        {

        }

        const std::string & name() const
        { return _name; }
        
        int value() const
        { return _value; }
    };
    
private:
    std::list<constant> _constants;

public:
    using parser::parser;
    void parse() override;
    std::string cpp_output() const;

    const std::list<constant> & constants()
    { return _constants; }
};

#endif
