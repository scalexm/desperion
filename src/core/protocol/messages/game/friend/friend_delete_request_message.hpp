//  Generated by desperion protocol_builder

#ifndef core_friend_delete_request_message_hpp
#define core_friend_delete_request_message_hpp

namespace network
{
    struct friend_delete_request_message : dofus_unit
    {
        int32_t account_id;
        
        int16_t id() const override
        { return 5603; } 
        
        friend_delete_request_message(const int32_t & account_id)
        {
            _data << account_id;
        }
        
        friend_delete_request_message(byte_buffer & data)
        {
            data >> account_id;
        }
    };
}

#endif
