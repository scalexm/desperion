//  Generated by desperion protocol_builder

#ifndef core_guild_member_leaving_message_hpp
#define core_guild_member_leaving_message_hpp

namespace network
{
    struct guild_member_leaving_message : dofus_unit
    {
        bool kicked;
        int32_t member_id;
        
        int16_t id() const override
        { return 5923; } 
        
        guild_member_leaving_message(const bool & kicked, const int32_t & member_id)
        {
            _data << kicked;
            _data << member_id;
        }
        
        guild_member_leaving_message(byte_buffer & data)
        {
            data >> kicked;
            data >> member_id;
        }
    };
}

#endif