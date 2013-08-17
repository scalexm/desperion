//  Generated by desperion protocol_builder

#ifndef core_exchange_craft_result_magic_with_object_desc_message_hpp
#define core_exchange_craft_result_magic_with_object_desc_message_hpp

namespace network
{
    struct exchange_craft_result_magic_with_object_desc_message : exchange_craft_result_with_object_desc_message
    {
        int8_t magic_pool_status;
        
        int16_t id() const override
        { return 6188; } 
        
        exchange_craft_result_magic_with_object_desc_message(const object_item_not_in_container_ptr & object_info, const int8_t & craft_result, const int8_t & magic_pool_status) : exchange_craft_result_with_object_desc_message { object_info,craft_result }
        {
            _data << magic_pool_status;
        }
        
        exchange_craft_result_magic_with_object_desc_message(byte_buffer & data) : exchange_craft_result_with_object_desc_message { data }
        {
            data >> magic_pool_status;
        }
    };
}

#endif
