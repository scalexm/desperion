//  Generated by desperion protocol_builder

#ifndef core_friend_set_warn_on_connection_message_hpp
#define core_friend_set_warn_on_connection_message_hpp

namespace network
{
    struct friend_set_warn_on_connection_message : dofus_unit
    {
        bool enable;
        
        int16_t id() const override
        { return 5602; } 
        
        friend_set_warn_on_connection_message(const bool & enable)
        {
            _data << enable;
        }
        
        friend_set_warn_on_connection_message(byte_buffer & data)
        {
            data >> enable;
        }
    };
}

#endif
