//  Generated by desperion protocol_builder

#ifndef core_inventory_weight_message_hpp
#define core_inventory_weight_message_hpp

namespace protocol
{
    struct inventory_weight_message : dofus_unit
    {
        int32_t weight;
        int32_t weight_max;
        
        int16_t id() const override
        { return 3009; } 
        
        inventory_weight_message(const int32_t & weight, const int32_t & weight_max)
        {
            _data << weight;
            _data << weight_max;
        }
        
        inventory_weight_message(byte_buffer & data)
        {
            data >> weight;
            data >> weight_max;
        }
    };
}

#endif
