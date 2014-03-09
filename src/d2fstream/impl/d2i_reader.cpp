//
//  d2i_reader.cpp
//  d2fstream
//
//  Created by Alexandre Martin on 31/07/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#include "../../core/common.hpp"
#include "d2i_reader_impl.hpp"

d2i_reader::d2i_reader(std::ifstream & file) : _impl { file }
{
}

d2i_reader::d2i_reader(std::ifstream && file) : d2i_reader { file }
{
}

d2i_reader::~d2i_reader()
{
    // willingly empty
}

std::string d2i_reader::read_text(int index)
{
    return _impl->read_text(index);
}

std::string d2i_reader::read_ui_text(const std::string& index)
{
    return _impl->read_ui_text(index);
}

std::unordered_map<int, std::string> d2i_reader::read_all_text()
{
    return _impl->read_all_text();
}

std::unordered_map<std::string, std::string> d2i_reader::read_all_ui_text()
{
    return _impl->read_all_ui_text();
}

bool d2i_reader::has_text(int index) const
{
    return _impl->has_text(index);
}

bool d2i_reader::has_ui_text(const std::string & index) const
{
    return _impl->has_ui_text(index);
}
