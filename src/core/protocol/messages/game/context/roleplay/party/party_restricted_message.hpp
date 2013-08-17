//  Generated by desperion protocol_builder

#ifndef core_party_restricted_message_hpp
#define core_party_restricted_message_hpp

namespace network
{
    struct party_restricted_message : abstract_party_message
    {
        bool restricted;
        
        int16_t id() const override
        { return 6175; } 
        
        party_restricted_message(const int32_t & party_id, const bool & restricted) : abstract_party_message { party_id }
        {
            _data << restricted;
        }
        
        party_restricted_message(byte_buffer & data) : abstract_party_message { data }
        {
            data >> restricted;
        }
    };
}

#endif
