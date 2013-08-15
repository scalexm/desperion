//
//  d2i_reader_impl.hpp
//  d2fstream
//
//  Created by Alexandre Martin on 31/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef d2fstream_d2i_reader_impl_hpp
#define d2fstream_d2i_reader_impl_hpp

#include "../d2i_reader.hpp"
#include "../../core/pimpl_impl.hpp"
#include "../../core/byte_buffer.hpp"

class d2i_reader::impl
{
private:
    std::unordered_map<int, int> _texts;
    std::unordered_map<std::string, int> _ui_texts;
    byte_buffer _buffer;

    std::string read(int);
public:
    impl(std::ifstream &);

    std::string read_text(int);
    std::string read_ui_text(const std::string &);
    std::unordered_map<int, std::string> read_all_text();
    std::unordered_map<std::string, std::string> read_all_ui_text();

    bool has_text(int) const;
    bool has_ui_text(const std::string &) const;
};

#endif
