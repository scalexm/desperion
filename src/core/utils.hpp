//
//  utils.hpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef core_utils_hpp
#define core_utils_hpp

#include <string>
#include <ostream>
#ifdef _WIN32
#include <Windows.h>
#endif
#include <sstream>

inline std::string operator "" _s(const char * str, size_t n)
{ return { str, n }; }

namespace utils
{
    std::string compute_md5_digest(const std::string &);

    enum print_color
    {
#ifdef _WIN32
        TRED = FOREGROUND_RED | FOREGROUND_INTENSITY,
        TGREEN = FOREGROUND_GREEN | FOREGROUND_INTENSITY,
        TYELLOW = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY,
        TNORMAL = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
        TWHITE = TNORMAL | FOREGROUND_INTENSITY,
        TBLUE = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY,
        TPURPLE = FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY,
#else
        TRED = 1,
        TGREEN = 2,
        TYELLOW = 3,
        TNORMAL = 4,
        TWHITE = 5,
        TBLUE = 6,
        TPURPLE = 7,
#endif
    };

#ifndef _WIN32
    namespace
    {
        const char * colorstrings[] =
        {
            "",
            "\033[22;31m",
            "\033[22;32m",
            "\033[01;33m",
            "\033[0m",
            "\033[01;37m",
            "\033[22;34m"
        };
    }
#endif

    template<print_color C>
    inline std::ostream & color(std::ostream & stream)
    {
#ifdef _WIN32
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
#else
        stream << colorstrings[C];
#endif
        return stream;
    }

    inline std::ostream & cendl(std::ostream & ss)
    {
        color<TNORMAL>(ss);
        return (ss << std::endl);
    }

    template<char S, class V>
    inline void split(const std::string & str, V callback)
    {
        std::string line;
        std::istringstream ss { str };
        while (std::getline(ss, line, S))
            callback(std::move(line));
    }
}

#endif
