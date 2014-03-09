//  Generated by desperion protocol_builder

#ifndef core_shortcut_bar_refresh_message_hpp
#define core_shortcut_bar_refresh_message_hpp

namespace protocol
{
    struct shortcut_bar_refresh_message : dofus_unit
    {
        int8_t bar_type;
        shortcut_ptr shortcut;
        
        int16_t id() const override
        { return 6229; } 
        
        shortcut_bar_refresh_message(const int8_t & bar_type, const shortcut_ptr & shortcut)
        {
            _data << bar_type;
            _data << shortcut->id() << shortcut->buffer();
        }
        
        shortcut_bar_refresh_message(byte_buffer & data)
        {
            data >> bar_type;
            int16_t shortcut_id;
            data >> shortcut_id;
            shortcut.reset(type_manager::get_shortcut(shortcut_id, data));
        }
    };
}

#endif
