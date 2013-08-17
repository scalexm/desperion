//  Generated by desperion protocol_builder

#ifndef core_shortcut_bar_add_error_message_hpp
#define core_shortcut_bar_add_error_message_hpp

namespace network
{
    struct shortcut_bar_add_error_message : dofus_unit
    {
        int8_t error;
        
        int16_t id() const override
        { return 6227; } 
        
        shortcut_bar_add_error_message(const int8_t & error)
        {
            _data << error;
        }
        
        shortcut_bar_add_error_message(byte_buffer & data)
        {
            data >> error;
        }
    };
}

#endif