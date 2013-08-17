//  Generated by desperion protocol_builder

#ifndef core_alliance_guild_leaving_message_hpp
#define core_alliance_guild_leaving_message_hpp

namespace network
{
    struct alliance_guild_leaving_message : dofus_unit
    {
        bool kicked;
        int32_t guild_id;
        
        int16_t id() const override
        { return 6399; } 
        
        alliance_guild_leaving_message(const bool & kicked, const int32_t & guild_id)
        {
            _data << kicked;
            _data << guild_id;
        }
        
        alliance_guild_leaving_message(byte_buffer & data)
        {
            data >> kicked;
            data >> guild_id;
        }
    };
}

#endif
