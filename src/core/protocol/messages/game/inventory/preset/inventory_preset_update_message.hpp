//  Generated by desperion protocol_builder

#ifndef core_inventory_preset_update_message_hpp
#define core_inventory_preset_update_message_hpp

namespace network
{
    struct inventory_preset_update_message : dofus_unit
    {
        preset_ptr preset;
        
        int16_t id() const override
        { return 6171; } 
        
        inventory_preset_update_message(const preset_ptr & preset)
        {
            _data << preset->buffer();
        }
        
        inventory_preset_update_message(byte_buffer & data)
        {
            preset = std::make_unique<preset>(data);
        }
    };
}

#endif
