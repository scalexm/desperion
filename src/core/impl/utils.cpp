//
//  utils.cpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#include "../common.hpp"
#include "../utils.hpp"
#include "third_party/md5.h"
#include <array>
#include <iomanip>

namespace utils
{
    // uses Aladdin's C code: md5.h/md5.c
    std::string compute_md5_digest(const std::string & src)
    {
        auto state = std::make_unique<md5_state_t>();
        std::array<md5_byte_t, 16> digest;
        md5_init(state.get());
        md5_append(state.get(), (const md5_byte_t *)src.c_str(), src.size());
        md5_finish(state.get(), digest.data());

        std::ostringstream oss;
        oss << std::hex << std::setfill('0');
        for (auto && value : digest)
            oss << std::setw(2) << static_cast<int>(value);
        return oss.str();
    }
}