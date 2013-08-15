//  Generated by desperion protocol_builder

#ifndef core_guild_membership_message_hpp
#define core_guild_membership_message_hpp

namespace network
{
    struct guild_membership_message : guild_joined_message
    {
        
        int16_t id() const override
        { return 5835; } 
        
        guild_membership_message(const guild_informations_ptr & guild_info, const unsigned_int_ptr & member_rights, const bool & enabled) : guild_joined_message { guild_info,member_rights,enabled }
        {
        }
        
        guild_membership_message(byte_buffer & data) : guild_joined_message { data }
        {
        }
    };
}

#endif