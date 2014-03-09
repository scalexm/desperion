//
//  dofus.hpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#ifndef core_dofus_hpp
#define core_dofus_hpp

#include "../byte_buffer.hpp"

namespace protocol
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

    namespace detail
    {
        inline uint8_t compute_type_len(size_t size)
        {
            if (size > 0xffff)
                return 3;
            else if (size > 0xff)
                return 2;
            else if (size > 0)
                return 1;
            else
                return 0;
        }

        inline void pack_packet(int16_t opcode, byte_buffer & header, size_t size)
        {
            auto compute = compute_type_len(size);
            int16_t val = (opcode << 2) | compute;
            header << val;
            switch (compute)
            {
                case 1:
                    header << static_cast<uint8_t>(size);
                    break;
                case 2:
                    header << static_cast<uint16_t>(size);
                    break;
                case 3:
                    header << static_cast<uint8_t>((size >> 0x10) & 0xff);
                    header << static_cast<uint16_t>(size & 0xffff);
                    break;
            }
        }
    }

    inline void fmt(byte_buffer & dest, const dofus_unit & message)
    {
        auto opcode = message.id();
        auto && src = message.buffer();
        detail::pack_packet(opcode, dest, src.size());
        dest << src;
    }
}

#endif
