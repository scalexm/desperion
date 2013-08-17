//  Generated by desperion protocol_builder

#ifndef core_guild_paddock_removed_message_hpp
#define core_guild_paddock_removed_message_hpp

namespace network
{
    struct guild_paddock_removed_message : dofus_unit
    {
        int32_t paddock_id;
        
        int16_t id() const override
        { return 5955; } 
        
        guild_paddock_removed_message(const int32_t & paddock_id)
        {
            _data << paddock_id;
        }
        
        guild_paddock_removed_message(byte_buffer & data)
        {
            data >> paddock_id;
        }
    };
}

#endif