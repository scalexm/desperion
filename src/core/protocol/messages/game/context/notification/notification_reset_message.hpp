//  Generated by desperion protocol_builder

#ifndef core_notification_reset_message_hpp
#define core_notification_reset_message_hpp

namespace protocol
{
    struct notification_reset_message : dofus_unit
    {
        
        int16_t id() const override
        { return 6089; } 
        
        notification_reset_message()
        {
        }
        
        notification_reset_message(byte_buffer & data)
        {
        }
    };
}

#endif
