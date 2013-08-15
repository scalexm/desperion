//
//  dofus.hpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef core_dofus_hpp
#define core_dofus_hpp

#include "../byte_buffer.hpp"

namespace network
{
    constexpr int DOFUS_VERSION_MAJOR = 2,
        DOFUS_VERSION_MINOR = 13,
        DOFUS_VERSION_RELEASE = 4,
        DOFUS_VERSION_REVISION = 76020,
        DOFUS_VERSION_PATCH = 1,
        DOFUS_VERSION_BUILD_TYPE = 0,

        PROTOCOL_REQUIRED_BUILD = 1534,
        PROTOCOL_BUILD = 1542;

    class dofus_unit
    {
    protected:
        byte_buffer _data;
    public:
        virtual ~dofus_unit() = default;
        virtual int16_t id() const = 0;

        const byte_buffer & buffer() const
        { return _data; }
    };

    inline bool get_bool_flag(int8_t flag, int8_t offset)
    {
        return (flag & (1 << offset)) != 0;
    }

    inline void set_bool_flag(int8_t & flag, int8_t offset, bool value)
    {
        flag = value ? (flag | (1 << offset)) : ((flag & 255) - (1 << offset));
    }
}

#endif
