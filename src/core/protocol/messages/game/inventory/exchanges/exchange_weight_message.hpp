//  Generated by desperion protocol_builder

#ifndef core_exchange_weight_message_hpp
#define core_exchange_weight_message_hpp

namespace protocol
{
    struct exchange_weight_message : dofus_unit
    {
        int32_t current_weight;
        int32_t max_weight;
        
        int16_t id() const override
        { return 5793; } 
        
        exchange_weight_message(const int32_t & current_weight, const int32_t & max_weight)
        {
            _data << current_weight;
            _data << max_weight;
        }
        
        exchange_weight_message(byte_buffer & data)
        {
            data >> current_weight;
            data >> max_weight;
        }
    };
}

#endif
