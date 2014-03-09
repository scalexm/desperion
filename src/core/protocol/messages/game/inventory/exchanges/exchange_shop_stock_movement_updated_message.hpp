//  Generated by desperion protocol_builder

#ifndef core_exchange_shop_stock_movement_updated_message_hpp
#define core_exchange_shop_stock_movement_updated_message_hpp

namespace protocol
{
    struct exchange_shop_stock_movement_updated_message : dofus_unit
    {
        object_item_to_sell_ptr object_info;
        
        int16_t id() const override
        { return 5909; } 
        
        exchange_shop_stock_movement_updated_message(const object_item_to_sell_ptr & object_info)
        {
            _data << object_info->buffer();
        }
        
        exchange_shop_stock_movement_updated_message(byte_buffer & data)
        {
            object_info = std::make_unique<object_item_to_sell>(data);
        }
    };
}

#endif
