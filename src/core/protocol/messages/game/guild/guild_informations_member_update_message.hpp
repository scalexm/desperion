//  Generated by desperion protocol_builder

#ifndef core_guild_informations_member_update_message_hpp
#define core_guild_informations_member_update_message_hpp

namespace protocol
{
    struct guild_informations_member_update_message : dofus_unit
    {
        guild_member_ptr member;
        
        int16_t id() const override
        { return 5597; } 
        
        guild_informations_member_update_message(const guild_member_ptr & member)
        {
            _data << member->buffer();
        }
        
        guild_informations_member_update_message(byte_buffer & data)
        {
            member = std::make_unique<guild_member>(data);
        }
    };
}

#endif
