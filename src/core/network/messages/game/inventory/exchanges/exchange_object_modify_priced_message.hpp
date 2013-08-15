//  Generated by desperion protocol_builder

#ifndef core_exchange_object_modify_priced_message_hpp
#define core_exchange_object_modify_priced_message_hpp

namespace network
{
    struct exchange_object_modify_priced_message : exchange_object_move_priced_message
    {
        
        int16_t id() const override
        { return 6238; } 
        
        exchange_object_modify_priced_message(const int32_t & price, const int32_t & object_u_i_d, const int32_t & quantity) : exchange_object_move_priced_message { price,object_u_i_d,quantity }
        {
        }
        
        exchange_object_modify_priced_message(byte_buffer & data) : exchange_object_move_priced_message { data }
        {
        }
    };
}

#endif
