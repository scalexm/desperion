//
//  d2i_writer.cpp
//  d2fstream
//
//  Created by Alexandre Martin on 31/07/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#include "../../core/common.hpp"
#include "../d2i_writer.hpp"
#include "../../core/byte_buffer.hpp"

void d2i_writer::add_text(int index, const std::string & text)
{
    _texts.emplace(index, text);
}

void d2i_writer::add_ui_text(const std::string & index, const std::string & text)
{
    _ui_texts.emplace(index, text);
}
bool d2i_writer::has_text(int index) const
{
    return _texts.find(index) != end(_texts);
}

bool d2i_writer::has_ui_text(const std::string & index) const
{
    return _ui_texts.find(index) != end(_ui_texts);
}

void d2i_writer::write(std::ofstream & file) const
{
    if (!file)
        throw std::runtime_error { "bad file" };
    byte_buffer buffer;
    buffer << 0;
    for (auto && it : _texts)
        buffer << it.second;
    auto ui_length = 0;
    for (auto && it : _ui_texts)
    {
        ui_length += 2 + it.first.size() + 4;
        buffer << it.second;
    }

    int header = buffer.tellp();

    buffer << static_cast<int>(_texts.size() * 9);
    auto offset = 4;
    for (auto && it : _texts)
    {
        buffer << it.first << false << offset;
        offset += 2 + it.second.size();
    }
    buffer << ui_length;
    for (auto && it : _ui_texts)
    {
        buffer << it.first << offset;
        offset += 2 + it.second.size();
    }

    buffer.seekp(0);
    buffer << header;
    file.write((const char*)&buffer[0], buffer.size());
}

void d2i_writer::write(std::ofstream && file) const
{
    write(file);
}
