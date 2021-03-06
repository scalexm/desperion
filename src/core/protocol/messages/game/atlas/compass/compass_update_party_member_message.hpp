//  Generated by desperion protocol_builder

#ifndef core_compass_update_party_member_message_hpp
#define core_compass_update_party_member_message_hpp

namespace protocol
{
    struct compass_update_party_member_message : compass_update_message
    {
        int32_t member_id;
        
        int16_t id() const override
        { return 5589; } 
        
        compass_update_party_member_message(const int8_t & type, const int16_t & world_x, const int16_t & world_y, const int32_t & member_id) : compass_update_message { type,world_x,world_y }
        {
            _data << member_id;
        }
        
        compass_update_party_member_message(byte_buffer & data) : compass_update_message { data }
        {
            data >> member_id;
        }
    };
}

#endif
