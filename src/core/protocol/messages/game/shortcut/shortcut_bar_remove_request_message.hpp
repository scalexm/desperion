//  Generated by desperion protocol_builder

#ifndef core_shortcut_bar_remove_request_message_hpp
#define core_shortcut_bar_remove_request_message_hpp

namespace protocol
{
    struct shortcut_bar_remove_request_message : dofus_unit
    {
        int8_t bar_type;
        int32_t slot;
        
        int16_t id() const override
        { return 6228; } 
        
        shortcut_bar_remove_request_message(const int8_t & bar_type, const int32_t & slot)
        {
            _data << bar_type;
            _data << slot;
        }
        
        shortcut_bar_remove_request_message(byte_buffer & data)
        {
            data >> bar_type;
            data >> slot;
        }
    };
}

#endif
