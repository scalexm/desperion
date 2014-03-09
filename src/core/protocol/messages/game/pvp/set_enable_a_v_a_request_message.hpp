//  Generated by desperion protocol_builder

#ifndef core_set_enable_a_v_a_request_message_hpp
#define core_set_enable_a_v_a_request_message_hpp

namespace protocol
{
    struct set_enable_a_v_a_request_message : dofus_unit
    {
        bool enable;
        
        int16_t id() const override
        { return 6443; } 
        
        set_enable_a_v_a_request_message(const bool & enable)
        {
            _data << enable;
        }
        
        set_enable_a_v_a_request_message(byte_buffer & data)
        {
            data >> enable;
        }
    };
}

#endif
