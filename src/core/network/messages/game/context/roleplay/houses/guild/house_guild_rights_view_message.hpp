//  Generated by desperion protocol_builder

#ifndef core_house_guild_rights_view_message_hpp
#define core_house_guild_rights_view_message_hpp

namespace network
{
    struct house_guild_rights_view_message : dofus_unit
    {
        
        int16_t id() const override
        { return 5700; } 
        
        house_guild_rights_view_message()
        {
        }
        
        house_guild_rights_view_message(byte_buffer & data)
        {
        }
    };
}

#endif
