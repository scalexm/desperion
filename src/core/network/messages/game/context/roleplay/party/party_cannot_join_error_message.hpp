//  Generated by desperion protocol_builder

#ifndef core_party_cannot_join_error_message_hpp
#define core_party_cannot_join_error_message_hpp

namespace network
{
    struct party_cannot_join_error_message : abstract_party_message
    {
        int8_t reason;
        
        int16_t id() const override
        { return 5583; } 
        
        party_cannot_join_error_message(const int32_t & party_id, const int8_t & reason) : abstract_party_message { party_id }
        {
            _data << reason;
        }
        
        party_cannot_join_error_message(byte_buffer & data) : abstract_party_message { data }
        {
            data >> reason;
        }
    };
}

#endif