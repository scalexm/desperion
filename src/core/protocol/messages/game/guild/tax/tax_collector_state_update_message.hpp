//  Generated by desperion protocol_builder

#ifndef core_tax_collector_state_update_message_hpp
#define core_tax_collector_state_update_message_hpp

namespace protocol
{
    struct tax_collector_state_update_message : dofus_unit
    {
        int32_t unique_id;
        int8_t state;
        
        int16_t id() const override
        { return 6455; } 
        
        tax_collector_state_update_message(const int32_t & unique_id, const int8_t & state)
        {
            _data << unique_id;
            _data << state;
        }
        
        tax_collector_state_update_message(byte_buffer & data)
        {
            data >> unique_id;
            data >> state;
        }
    };
}

#endif
