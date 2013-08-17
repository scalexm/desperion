//  Generated by desperion protocol_builder

#ifndef core_party_member_remove_message_hpp
#define core_party_member_remove_message_hpp

namespace network
{
    struct party_member_remove_message : abstract_party_event_message
    {
        int32_t leaving_player_id;
        
        int16_t id() const override
        { return 5579; } 
        
        party_member_remove_message(const int32_t & party_id, const int32_t & leaving_player_id) : abstract_party_event_message { party_id }
        {
            _data << leaving_player_id;
        }
        
        party_member_remove_message(byte_buffer & data) : abstract_party_event_message { data }
        {
            data >> leaving_player_id;
        }
    };
}

#endif
