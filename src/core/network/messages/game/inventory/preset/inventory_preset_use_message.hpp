//  Generated by desperion protocol_builder

#ifndef core_inventory_preset_use_message_hpp
#define core_inventory_preset_use_message_hpp

namespace network
{
    struct inventory_preset_use_message : dofus_unit
    {
        int8_t preset_id;
        
        int16_t id() const override
        { return 6167; } 
        
        inventory_preset_use_message(const int8_t & preset_id)
        {
            _data << preset_id;
        }
        
        inventory_preset_use_message(byte_buffer & data)
        {
            data >> preset_id;
        }
    };
}

#endif
