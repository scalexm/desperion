//
//  message_file.hpp
//  protocol_builder
//
//  Created by Alexandre Martin on 05/08/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#ifndef protocol_builder_network_file_hpp
#define protocol_builder_network_file_hpp

#include "parser.hpp"
#include <list>
#include <unordered_map>

class network_file : public parser
{
public:
    class field
    {
    private:
        std::string _name;
        std::string _type;
        bool _instance_of;
        int _bit;
        bool _vector;

    public:
        field(std::string name, std::string type, bool vector, bool instance_of, int bit)
            : _name { std::move(name) }, _vector { vector }, _type { std::move(type) },
            _instance_of { instance_of }, _bit { bit }
        {
        }

        const std::string & name() const
        { return _name; }

        const std::string & type() const
        { return _type; }

        bool is_instance_of() const
        { return _instance_of; }
        
        int bit() const
        { return _bit; }
        
        bool is_vector() const
        { return _vector; }
    };

private:
    std::list<field> _fields;
    int _id = -1;

public:
    using parser::parser;
    void parse() override;
    std::string cpp_output(const std::unordered_map<std::string, network_file> &) const;

    const std::list<field> & fields() const
    { return _fields; }

    int id() const
    { return _id; }
};

#endif
