//
//  d2i_writer.hpp
//  d2fstream
//
//  Created by Alexandre Martin on 31/07/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#ifndef d2fstream_d2i_writer_hpp
#define d2fstream_d2i_writer_hpp

#include <map>
#include <string>
#include <fstream>

class d2i_writer
{
private:
    // using map instead of unordered_map to get consistent ordering (useful for ::write)
    std::map<int, std::string> _texts;
    std::map<std::string, std::string> _ui_texts;
public:
    d2i_writer() = default;

    void add_text(int, const std::string &);
    void add_ui_text(const std::string &, const std::string &);

    bool has_text(int) const;
    bool has_ui_text(const std::string &) const;

    void write(std::ofstream &) const;
    void write(std::ofstream &&) const;
};

#endif
