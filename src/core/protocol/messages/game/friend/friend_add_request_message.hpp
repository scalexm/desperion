//  Generated by desperion protocol_builder

#ifndef core_friend_add_request_message_hpp
#define core_friend_add_request_message_hpp

namespace protocol
{
    struct friend_add_request_message : dofus_unit
    {
        std::string name;
        
        int16_t id() const override
        { return 4004; } 
        
        friend_add_request_message(const std::string & name)
        {
            _data << name;
        }
        
        friend_add_request_message(byte_buffer & data)
        {
            data >> name;
        }
    };
}

#endif
