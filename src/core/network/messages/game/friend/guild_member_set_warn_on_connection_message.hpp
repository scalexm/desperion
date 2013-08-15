//  Generated by desperion protocol_builder

#ifndef core_guild_member_set_warn_on_connection_message_hpp
#define core_guild_member_set_warn_on_connection_message_hpp

namespace network
{
    struct guild_member_set_warn_on_connection_message : dofus_unit
    {
        bool enable;
        
        int16_t id() const override
        { return 6159; } 
        
        guild_member_set_warn_on_connection_message(const bool & enable)
        {
            _data << enable;
        }
        
        guild_member_set_warn_on_connection_message(byte_buffer & data)
        {
            data >> enable;
        }
    };
}

#endif
