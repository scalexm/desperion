//  Generated by desperion protocol_builder

#ifndef core_guild_level_up_message_hpp
#define core_guild_level_up_message_hpp

namespace network
{
    struct guild_level_up_message : dofus_unit
    {
        int8_t new_level;
        
        int16_t id() const override
        { return 6062; } 
        
        guild_level_up_message(const int8_t & new_level)
        {
            _data << new_level;
        }
        
        guild_level_up_message(byte_buffer & data)
        {
            data >> new_level;
        }
    };
}

#endif
