//  Generated by desperion protocol_builder

#ifndef core_friend_spouse_follow_with_compass_request_message_hpp
#define core_friend_spouse_follow_with_compass_request_message_hpp

namespace protocol
{
    struct friend_spouse_follow_with_compass_request_message : dofus_unit
    {
        bool enable;
        
        int16_t id() const override
        { return 5606; } 
        
        friend_spouse_follow_with_compass_request_message(const bool & enable)
        {
            _data << enable;
        }
        
        friend_spouse_follow_with_compass_request_message(byte_buffer & data)
        {
            data >> enable;
        }
    };
}

#endif
