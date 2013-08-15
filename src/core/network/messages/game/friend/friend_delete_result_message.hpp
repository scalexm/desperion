//  Generated by desperion protocol_builder

#ifndef core_friend_delete_result_message_hpp
#define core_friend_delete_result_message_hpp

namespace network
{
    struct friend_delete_result_message : dofus_unit
    {
        bool success;
        std::string name;
        
        int16_t id() const override
        { return 5601; } 
        
        friend_delete_result_message(const bool & success, const std::string & name)
        {
            _data << success;
            _data << name;
        }
        
        friend_delete_result_message(byte_buffer & data)
        {
            data >> success;
            data >> name;
        }
    };
}

#endif
