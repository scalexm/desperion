//  Generated by desperion protocol_builder

#ifndef core_house_guild_rights_message_hpp
#define core_house_guild_rights_message_hpp

namespace network
{
    struct house_guild_rights_message : dofus_unit
    {
        int16_t house_id;
        guild_informations_ptr guild_info;
        unsigned_int_ptr rights;
        
        int16_t id() const override
        { return 5703; } 
        
        house_guild_rights_message(const int16_t & house_id, const guild_informations_ptr & guild_info, const unsigned_int_ptr & rights)
        {
            _data << house_id;
            _data << guild_info->buffer();
            _data << rights->buffer();
        }
        
        house_guild_rights_message(byte_buffer & data)
        {
            data >> house_id;
            guild_info = std::make_unique<guild_informations>(data);
            rights = std::make_unique<unsigned_int>(data);
        }
    };
}

#endif