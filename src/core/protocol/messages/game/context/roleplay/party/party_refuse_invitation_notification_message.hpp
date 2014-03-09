//  Generated by desperion protocol_builder

#ifndef core_party_refuse_invitation_notification_message_hpp
#define core_party_refuse_invitation_notification_message_hpp

namespace protocol
{
    struct party_refuse_invitation_notification_message : abstract_party_event_message
    {
        int32_t guest_id;
        
        int16_t id() const override
        { return 5596; } 
        
        party_refuse_invitation_notification_message(const int32_t & party_id, const int32_t & guest_id) : abstract_party_event_message { party_id }
        {
            _data << guest_id;
        }
        
        party_refuse_invitation_notification_message(byte_buffer & data) : abstract_party_event_message { data }
        {
            data >> guest_id;
        }
    };
}

#endif
