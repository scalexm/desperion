//  Generated by desperion protocol_builder

#ifndef core_exchange_start_ok_tax_collector_message_hpp
#define core_exchange_start_ok_tax_collector_message_hpp

namespace protocol
{
    struct exchange_start_ok_tax_collector_message : dofus_unit
    {
        int32_t collector_id;
        std::vector<object_item_ptr> objects_infos;
        int32_t gold_info;
        
        int16_t id() const override
        { return 5780; } 
        
        exchange_start_ok_tax_collector_message(const int32_t & collector_id, const std::vector<object_item_ptr> & objects_infos, const int32_t & gold_info)
        {
            _data << collector_id;
            _data << static_cast<int16_t>(objects_infos.size());
            for (auto && i : objects_infos)
                _data << i->buffer();
            _data << gold_info;
        }
        
        exchange_start_ok_tax_collector_message(byte_buffer & data)
        {
            data >> collector_id;
            int16_t objects_infos_size;
            data >> objects_infos_size;
            objects_infos.resize(objects_infos_size);
            for (int16_t i = 0; i < objects_infos_size; ++i)
                objects_infos[i] = std::make_unique<object_item>(data);
            data >> gold_info;
        }
    };
}

#endif
