//  Generated by desperion protocol_builder

#ifndef core_party_abdicate_throne_message_hpp
#define core_party_abdicate_throne_message_hpp

namespace network
{
    struct party_abdicate_throne_message : abstract_party_message
    {
        int32_t player_id;
        
        int16_t id() const override
        { return 6080; } 
        
        party_abdicate_throne_message(const int32_t & party_id, const int32_t & player_id) : abstract_party_message { party_id }
        {
            _data << player_id;
        }
        
        party_abdicate_throne_message(byte_buffer & data) : abstract_party_message { data }
        {
            data >> player_id;
        }
    };
}

#endif
