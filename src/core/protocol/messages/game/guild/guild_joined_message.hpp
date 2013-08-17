//  Generated by desperion protocol_builder

#ifndef core_guild_joined_message_hpp
#define core_guild_joined_message_hpp

namespace network
{
    struct guild_joined_message : dofus_unit
    {
        guild_informations_ptr guild_info;
        unsigned_int_ptr member_rights;
        bool enabled;
        
        int16_t id() const override
        { return 5564; } 
        
        guild_joined_message(const guild_informations_ptr & guild_info, const unsigned_int_ptr & member_rights, const bool & enabled)
        {
            _data << guild_info->buffer();
            _data << member_rights->buffer();
            _data << enabled;
        }
        
        guild_joined_message(byte_buffer & data)
        {
            guild_info = std::make_unique<guild_informations>(data);
            member_rights = std::make_unique<unsigned_int>(data);
            data >> enabled;
        }
    };
}

#endif