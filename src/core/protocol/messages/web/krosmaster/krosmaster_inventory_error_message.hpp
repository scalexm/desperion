//  Generated by desperion protocol_builder

#ifndef core_krosmaster_inventory_error_message_hpp
#define core_krosmaster_inventory_error_message_hpp

namespace protocol
{
    struct krosmaster_inventory_error_message : dofus_unit
    {
        int8_t reason;
        
        int16_t id() const override
        { return 6343; } 
        
        krosmaster_inventory_error_message(const int8_t & reason)
        {
            _data << reason;
        }
        
        krosmaster_inventory_error_message(byte_buffer & data)
        {
            data >> reason;
        }
    };
}

#endif
