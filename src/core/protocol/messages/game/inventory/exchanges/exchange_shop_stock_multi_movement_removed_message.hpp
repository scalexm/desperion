//  Generated by desperion protocol_builder

#ifndef core_exchange_shop_stock_multi_movement_removed_message_hpp
#define core_exchange_shop_stock_multi_movement_removed_message_hpp

namespace protocol
{
    struct exchange_shop_stock_multi_movement_removed_message : dofus_unit
    {
        std::vector<int32_t> object_id_list;
        
        int16_t id() const override
        { return 6037; } 
        
        exchange_shop_stock_multi_movement_removed_message(const std::vector<int32_t> & object_id_list)
        {
            _data << static_cast<int16_t>(object_id_list.size());
            for (auto && i : object_id_list)
                _data << i;
        }
        
        exchange_shop_stock_multi_movement_removed_message(byte_buffer & data)
        {
            int16_t object_id_list_size;
            data >> object_id_list_size;
            object_id_list.resize(object_id_list_size);
            for (int16_t i = 0; i < object_id_list_size; ++i)
                data >> object_id_list[i];
        }
    };
}

#endif
