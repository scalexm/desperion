//  Generated by desperion protocol_builder

#ifndef core_friend_warn_on_level_gain_state_message_hpp
#define core_friend_warn_on_level_gain_state_message_hpp

namespace network
{
    struct friend_warn_on_level_gain_state_message : dofus_unit
    {
        bool enable;
        
        int16_t id() const override
        { return 6078; } 
        
        friend_warn_on_level_gain_state_message(const bool & enable)
        {
            _data << enable;
        }
        
        friend_warn_on_level_gain_state_message(byte_buffer & data)
        {
            data >> enable;
        }
    };
}

#endif
