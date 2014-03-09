//  Generated by desperion protocol_builder

#ifndef core_party_invitation_details_request_message_hpp
#define core_party_invitation_details_request_message_hpp

namespace protocol
{
    struct party_invitation_details_request_message : abstract_party_message
    {
        
        int16_t id() const override
        { return 6264; } 
        
        party_invitation_details_request_message(const int32_t & party_id) : abstract_party_message { party_id }
        {
        }
        
        party_invitation_details_request_message(byte_buffer & data) : abstract_party_message { data }
        {
        }
    };
}

#endif
