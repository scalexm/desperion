//  Generated by desperion protocol_builder

#ifndef core_exchange_craft_information_object_message_hpp
#define core_exchange_craft_information_object_message_hpp

namespace network
{
    struct exchange_craft_information_object_message : exchange_craft_result_with_object_id_message
    {
        int32_t player_id;
        
        int16_t id() const override
        { return 5794; } 
        
        exchange_craft_information_object_message(const int32_t & object_generic_id, const int8_t & craft_result, const int32_t & player_id) : exchange_craft_result_with_object_id_message { object_generic_id,craft_result }
        {
            _data << player_id;
        }
        
        exchange_craft_information_object_message(byte_buffer & data) : exchange_craft_result_with_object_id_message { data }
        {
            data >> player_id;
        }
    };
}

#endif