//  Generated by desperion protocol_builder

#ifndef core_basic_no_operation_message_hpp
#define core_basic_no_operation_message_hpp

namespace protocol
{
    struct basic_no_operation_message : dofus_unit
    {
        
        int16_t id() const override
        { return 176; } 
        
        basic_no_operation_message()
        {
        }
        
        basic_no_operation_message(byte_buffer & data)
        {
        }
    };
}

#endif
