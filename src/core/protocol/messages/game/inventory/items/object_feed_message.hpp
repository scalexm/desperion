//  Generated by desperion protocol_builder

#ifndef core_object_feed_message_hpp
#define core_object_feed_message_hpp

namespace network
{
    struct object_feed_message : dofus_unit
    {
        int32_t object_u_i_d;
        int32_t food_u_i_d;
        int16_t food_quantity;
        
        int16_t id() const override
        { return 6290; } 
        
        object_feed_message(const int32_t & object_u_i_d, const int32_t & food_u_i_d, const int16_t & food_quantity)
        {
            _data << object_u_i_d;
            _data << food_u_i_d;
            _data << food_quantity;
        }
        
        object_feed_message(byte_buffer & data)
        {
            data >> object_u_i_d;
            data >> food_u_i_d;
            data >> food_quantity;
        }
    };
}

#endif
