//
//  network_file.cpp
//  protocol_builder
//
//  Created by Alexandre Martin on 06/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "network_file.hpp"
#include "output_helper.hpp"
#include <regex>
#include <algorithm>

void network_file::parse()
{
    const std::regex id_pattern { R"(return (\d+);)" };
    const std::regex method_pattern {
        R"(public function serializeAs_\w+\(param1:IDataOutput\) : void\s?\{\s?\s?)"
    };
    const std::regex primitive_write_pattern { R"(param1.write(\w+)\(this.(\w+)\))" };
    const std::regex object_write_pattern { R"(this.(\w+).serializeAs_(\w+)\(param1\))" };
    const std::regex instance_write_pattern { R"(this.(\w+).serialize\()" };
    const std::regex primitive_vector_pattern { R"(param1.write(\w+)\(this.(\w+)\[\w+\]\))" };
    const std::regex object_vector_pattern { R"(\(this.(\w+)\[\w+\] as (\w+)\).serializeAs)" };
    const std::regex instance_vector_pattern { R"(\(this.(\w+)\[\w+\] as (\w+)\).serialize\()" };
    const std::regex bit_pattern { R"(BooleanByteWrapper.setFlag\(\w+, (\d+), this.(\w+)\))" };

    std::smatch result;
    if (!std::regex_search(_content, result, id_pattern))
        throw std::runtime_error { "malformated file: can't find protocol id" };
    _id = std::stoi(result[1]);

    auto it = std::sregex_iterator(std::begin(_content), std::end(_content), method_pattern);
    auto method = _content.substr(it->position() + it->str().size());
    std::istringstream ss { method };
    std::string line;
    auto level = 1;
    while (std::getline(ss, line))
    {
        level += std::count(std::begin(line), std::end(line), '{');
        level -= std::count(std::begin(line), std::end(line), '}');
        if (level == 0)
            break;
        if (std::regex_search(line, result, primitive_write_pattern))
            _fields.emplace_back(result[2], result[1], false, false, -1);
        else if (std::regex_search(line, result, object_write_pattern))
            _fields.emplace_back(result[1], result[2], false, false, -1);
        else if (std::regex_search(line, result, instance_write_pattern))
        {
            auto name = result[1].str();;
            std::regex type_pattern { std::string { "public var " } + name + R"(:(\w+))" };
            if (std::regex_search(_content, result, type_pattern))
                _fields.emplace_back(std::move(name), result[1], false, true, -1);
        }
        else if (std::regex_search(line, result, primitive_vector_pattern))
            _fields.emplace_back(result[2], result[1], true, false, -1);
        else if (std::regex_search(line, result, object_vector_pattern))
            _fields.emplace_back(result[1], result[2], true, false, -1);
        else if (std::regex_search(line, result, instance_vector_pattern))
            _fields.emplace_back(result[1], result[2], true, true, -1);
        else if (std::regex_search(line, result, bit_pattern))
            _fields.emplace_back(result[2], "Boolean", false, false, std::stoi(result[1]));
    }
}


/*
 cpp output
 yeah i know, i'm not that goot at outputting formatted things
 */

std::list<field> get_base_fields(const std::string & name,
                                 const std::unordered_map<std::string, network_file> & files)
{
    if (name == "NetworkMessage" || name == "Object")
        return { };
    auto & file = files.at(name);
    auto fields = file.fields();
    fields.splice(std::end(fields), get_base_fields(file.inheritance(), files));
    return fields;
}

std::string get_cpp_type(const std::string & type, bool vector)
{
    std::string real_type;
    if (type == "Byte")
        return "int8_t";
    else if (type == "Double")
        return "double";
    else if (type == "Short")
        return "int16_t";
    else if (type == "Int")
        return "int32_t";
    else if (type == "UTF")
        return "std::string";
    else if (type == "Boolean")
        return "bool";
    return to_cpp_case(type) + "_ptr";
}

std::string get_real_type(const field & f)
{
    return f.is_vector() ? "std::vector<" + f.type() + ">" : f.type();
}

std::string remove_ptr(const std::string & type)
{
    return type.substr(0, type.size() - 4);
}

bool is_serializable(const std::string & type)
{
    return type == "int8_t" || type == "int16_t" || type == "int32_t" || type == "double"
    || type == "std::string" || type == "bool" || type == "std::vector<int8_t>";
}

bool read_field(output & o, const field & f, bool flagged, bool from_vector)
{
    if (is_serializable(get_real_type(f)) && f.bit() == -1)
        o.next() << "data >> " << f.name() << ";";
    else if (f.bit() != -1)
    {
        if (!flagged)
        {
            o.next() << "int8_t flag;";
            flagged = true;
        }
        if(f.bit() == 0)
            o.next() << "data >> flag;";
        o.next() << f.name() << " = get_bool_flag(flag, " << f.bit() << ");";
    }
    else if (f.is_vector())
    {
        std::string size = f.name() + "_size";
        o.next() << "int16_t " << size << ";";
        o.next() << "data >> " << size << ";";
        o.next() << f.name() << ".resize(" << size << ");";
        o.next() << "for (int16_t i = 0; i < " << size << "; ++i)";
        o.indent();
        read_field(o, { f.name() + "[i]", f.type(), false, f.is_instance_of(), f.bit() },
                   false, true);
        o.unindent();
    }
    else if (f.is_instance_of())
    {
        std::string id = from_vector ? "p" : f.name() + "_id";
        if (from_vector)
        {
            o.unindent().next() << "{";
            o.indent();
        }
        o.next() << "int16_t " << id << ";";
        o.next() << "data >> " << id << ";";
        o.next() << f.name() << ".reset(type_manager::get_" << remove_ptr(f.type())
        << "(" << id << ", data));";
        if (from_vector)
        {
            o.unindent().next() << "}";
            o.indent();
        }
    }
    else
        o.next() << f.name() << " = std::make_unique<" << remove_ptr(f.type()) << ">(data);";
    return flagged;
}

bool write_field(output & o, const field & f, bool flagged)
{
    if (flagged && f.bit() == -1)
    {
        o.next() << "_data << flag;";
        flagged = false;
    }
    if (is_serializable(get_real_type(f)) && f.bit() == -1)
        o.next() << "_data << " << f.name() << ";";
    else if (f.bit() != -1)
    {
        if (!flagged)
        {
            o.next() << "int8_t flag = 0;";
            flagged = true;
        }
        else if(f.bit() == 0)
            o.next() << "flag = 0;";
        o.next() << "set_bool_flag(flag, " << f.bit() << ", " << f.name() << ");";
        if (f.bit() == 7)
            o.next() << "_data << flag;";
    }
    else if (f.is_vector())
    {
        o.next() << "_data << static_cast<int16_t>(" << f.name() << ".size());";
        o.next() << "for (auto && i : " << f.name() << ")";
        o.indent();
        write_field(o, { "i", f.type(), false, f.is_instance_of(), f.bit() }, false);
        o.unindent();
    }
    else if (f.is_instance_of())
        o.next() << "_data << " << f.name() << "->id() << " << f.name() << "->buffer();";
    else
        o.next() << "_data << " << f.name() << "->buffer();";
    return flagged;
}

std::string network_file::cpp_output(const std::unordered_map<std::string, network_file>
                                     & files) const
{
    auto name = to_cpp_case(_class_name);
    auto base_name = to_cpp_case(_inheritance);
    auto casify = [](const field & f)
    {
        return field { to_cpp_case(f.name()), get_cpp_type(f.type(), f.is_vector()), f.is_vector(),
            f.is_instance_of(), f.bit() };
    };

    auto fields = _fields;
    std::transform(std::begin(fields), std::end(fields), std::begin(fields), casify);
    
    auto base_fields = get_base_fields(_inheritance, files);
    std::transform(std::begin(base_fields), std::end(base_fields),
                   std::begin(base_fields), casify);
    
    auto all_fields = base_fields;
    all_fields.insert(std::end(all_fields), std::begin(fields), std::end(fields));
    
    output o;
    o << "//  Generated by desperion protocol_builder";
    o.next().next() << "#ifndef core_" << name << "_hpp";
    o.next() << "#define core_" << name << "_hpp";
    o.next().next() << "namespace network";
    o.next() << "{";
    o.indent().next() << "struct " << name << " : ";
    if (_inheritance != "NetworkMessage" && _inheritance != "Object")
        o << base_name;
    else
        o << "dofus_unit";
    o.next() << "{";
    o.indent();
    for (auto && f : fields)
        o.next() << get_real_type(f) << " " << f.name() << ";";

    o.next().next() << "int16_t id() const override";
    o.next() << "{ return " << _id << "; } ";

    /* serialization */
    o.next().next() << name << "(";
    auto first = true;
    for (auto && f : all_fields)
    {
        if (!first)
            o << ", ";
        first = false;
        o << "const " << get_real_type(f) << " & " << f.name();
    }
    o << ")";
    if (!base_fields.empty())
    {
        o << " : " << base_name << " { ";
        first = true;
        for (auto && f : base_fields)
        {
            if (!first)
                o << ",";
            first = false;
            o << f.name();
        }
        o << " }";
    }
    o.next() << "{";
    o.indent();
    auto flagged = false;
    for (auto && f : fields)
        flagged = write_field(o, f, flagged);
    if (flagged)
        o.next() << "_data << flag;";
    o.unindent().next() << "}";

    /* deserialization */
    o.next().next() << name << "(byte_buffer & data)";
    if (_inheritance != "NetworkMessage" && _inheritance != "Object")
        o << " : " << base_name << " { data }";
    o.next() << "{";
    o.indent();
    flagged = false;
    for (auto && f : fields)
        flagged = read_field(o, f, flagged, false);
    o.unindent().next() << "}";

    o.unindent().next() << "};";
    if (_class_name.find("Message") == std::string::npos)
        o.next().next() << "using " << name << "_ptr = std::unique_ptr<" << name << ">;";
    o.unindent().next() << "}";
    o.next().next() << "#endif";
    return o.next().str();
}