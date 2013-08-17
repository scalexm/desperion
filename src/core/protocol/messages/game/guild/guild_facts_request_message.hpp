//  Generated by desperion protocol_builder

#ifndef core_guild_facts_request_message_hpp
#define core_guild_facts_request_message_hpp

namespace network
{
    struct guild_facts_request_message : dofus_unit
    {
        int32_t guild_id;
        
        int16_t id() const override
        { return 6404; } 
        
        guild_facts_request_message(const int32_t & guild_id)
        {
            _data << guild_id;
        }
        
        guild_facts_request_message(byte_buffer & data)
        {
            data >> guild_id;
        }
    };
}

#endif