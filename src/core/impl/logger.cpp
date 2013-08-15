//
//  logger.cpp
//  core
//
//  Created by Alexandre Martin on 29/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "../common.hpp"
#include "../logger.hpp"
#include <boost/filesystem.hpp>
#include <array>
#include <sstream>
#include <boost/lexical_cast.hpp>

/* log_folder */

logger::log_folder::log_folder(std::string prefix) : _prefix { std::move(prefix) }
{
    boost::filesystem::create_directory(_prefix);
}

auto logger::log_folder::write_date() -> log_folder &
{
    std::array<char, 15> hour;
    auto rawtime = std::time(nullptr);
    std::strftime(hour.data(), hour.size(), "%y-%m-%d.log", std::localtime(&rawtime));
    if (_hour.find(hour.data()) == std::string::npos) // check if date changed
    {
        _file.close();
        _hour = hour.data();
        _file.open(_prefix + "/" + _hour, std::ios::app);
    }
    std::strftime(hour.data(), hour.size(), "[%H:%M]", std::localtime(&rawtime));
    _file << hour.data();
    return *this;
}


/* logger */

logger::logger(std::string prefix) : _prefix { std::move(prefix) }
{
}

void logger::set_targets(const std::list<std::string> & targets)
{
    _folders.clear();
    for (auto && target : targets)
    {
        _folders.emplace(std::piecewise_construct, std::forward_as_tuple(target),
                         std::forward_as_tuple(_prefix + "/" + target));
    }
}

std::ostream & logger::operator ()(const std::string & name, const std::string & file, int line)
{
    static std::ostringstream empty;
    auto it = _folders.find(name);
    if (it == end(_folders))
    {
        empty.setstate(std::ios::badbit);
        return empty;
    }
    auto debug_info = "(" + file + ":" + boost::lexical_cast<std::string>(line) + ") ";
    return (it->second.write_date() << debug_info);
}
