//
//  statistics_center.hpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef core_statistics_center_hpp
#define core_statistics_center_hpp

// only used in release to get simple benchmark statistics about packets processing
#ifndef DEBUG

#include "singleton.hpp"
#include <unordered_map>

class statistics_center : public singleton<statistics_center>
{
    friend class singleton<statistics_center>;
public:
    void stat_processing_time(uint16_t, int64_t);
    int64_t get_processing_time(uint16_t);

    ~statistics_center();
private:
    std::unordered_map<uint16_t, std::pair<uint64_t, int64_t>> _times;
    int _major, _minor, _release;

    statistics_center(int, int, int);
};

#endif

#endif
