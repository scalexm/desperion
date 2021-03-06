//  Generated by desperion protocol_builder

#ifndef core_party_invitation_cancelled_for_guest_message_hpp
#define core_party_invitation_cancelled_for_guest_message_hpp

namespace protocol
{
    struct party_invitation_cancelled_for_guest_message : abstract_party_message
    {
        int32_t canceler_id;
        
        int16_t id() const override
        { return 6256; } 
        
        party_invitation_cancelled_for_guest_message(const int32_t & party_id, const int32_t & canceler_id) : abstract_party_message { party_id }
        {
            _data << canceler_id;
        }
        
        party_invitation_cancelled_for_guest_message(byte_buffer & data) : abstract_party_message { data }
        {
            data >> canceler_id;
        }
    };
}

#endif
