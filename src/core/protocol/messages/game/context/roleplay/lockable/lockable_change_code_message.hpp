//  Generated by desperion protocol_builder

#ifndef core_lockable_change_code_message_hpp
#define core_lockable_change_code_message_hpp

namespace network
{
    struct lockable_change_code_message : dofus_unit
    {
        std::string code;
        
        int16_t id() const override
        { return 5666; } 
        
        lockable_change_code_message(const std::string & code)
        {
            _data << code;
        }
        
        lockable_change_code_message(byte_buffer & data)
        {
            data >> code;
        }
    };
}

#endif
