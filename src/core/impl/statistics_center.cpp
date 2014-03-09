//
//  statistics_center.cpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#ifndef DEBUG

#include "../common.hpp"
#include "../statistics_center.hpp"
#include "../utils.hpp"
#include <vector>
#include <fstream>
#include <sstream>

statistics_center::statistics_center(int major, int minor, int release)
    : _major { major }, _minor { minor }, _release { release }
{
    std::ostringstream filename;
    filename << "stats_" << _major << "." << _minor << "." << _release;
    std::ifstream file { filename.str() };
    if (file)
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::vector<uint64_t> table;
            utils::split<' '>(line, [&table](std::string && str)
                              {
                                  table.emplace_back(atoi(str.c_str()));
                              });
            if (table.size() < 3)
                continue;
            _times[table[0]] = std::make_pair(table[1], table[2]);
        }
    }
}

statistics_center::~statistics_center()
{
    std::ostringstream filename;
    filename << "stats_" << _major << "." << _minor << "." << _release;
    std::ofstream file { filename.str() };
    if (!file)
        return;
    for (auto && it : _times)
        file << it.first << " " << it.second.first << " " << it.second.second << "\r\n";
}

void statistics_center::stat_processing_time(uint16_t opcode, int64_t duration)
{
    auto it = _times.find(opcode);
    if (it == end(_times))
        _times[opcode] = std::make_pair(1, duration);
    else
    {
        auto avg_time = _times[opcode].second;
        auto count = _times[opcode].first;
        _times[opcode].second = (avg_time * count + duration) / (count + 1);
        ++_times[opcode].first;
    }
}

int64_t statistics_center::get_processing_time(uint16_t opcode)
{
    auto it = _times.find(opcode);
    if (it == end(_times))
        return 0;
    return it->second.second;
}

#endif