//  Generated by desperion protocol_builder

#ifndef core_object_item_to_sell_in_bid_hpp
#define core_object_item_to_sell_in_bid_hpp

namespace protocol
{
    struct object_item_to_sell_in_bid : object_item_to_sell
    {
        int16_t unsold_delay;
        
        int16_t id() const override
        { return 164; } 
        
        object_item_to_sell_in_bid(const int16_t & object_g_i_d, const int16_t & power_rate, const bool & over_max, const std::vector<object_effect_ptr> & effects, const int32_t & object_u_i_d, const int32_t & quantity, const int32_t & object_price, const int16_t & unsold_delay) : object_item_to_sell { object_g_i_d,power_rate,over_max,effects,object_u_i_d,quantity,object_price }
        {
            _data << unsold_delay;
        }
        
        object_item_to_sell_in_bid(byte_buffer & data) : object_item_to_sell { data }
        {
            data >> unsold_delay;
        }
    };
    
    using object_item_to_sell_in_bid_ptr = std::unique_ptr<object_item_to_sell_in_bid>;
}

#endif
