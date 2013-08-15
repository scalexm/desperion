//
//  d2i_reader.hpp
//  d2fstream
//
//  Created by Alexandre Martin on 31/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef d2fstream_d2i_reader_hpp
#define d2fstream_d2i_reader_hpp

#include "../core/pimpl.hpp"
#include <unordered_map>
#include <string>

class d2i_reader
{
private:
    class impl;
    pimpl<impl> _impl;

public:
    d2i_reader(std::ifstream &);
    d2i_reader(std::ifstream &&);
    ~d2i_reader();

    std::string read_text(int);
    std::string read_ui_text(const std::string &);
    std::unordered_map<int, std::string> read_all_text();
    std::unordered_map<std::string, std::string> read_all_ui_text();

    bool has_text(int) const;
    bool has_ui_text(const std::string &) const;
};

#endif
