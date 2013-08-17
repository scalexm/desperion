//  Generated by desperion protocol_builder

#ifndef core_object_item_hpp
#define core_object_item_hpp

namespace network
{
    struct object_item : item
    {
        int8_t position;
        int16_t object_g_i_d;
        int16_t power_rate;
        bool over_max;
        std::vector<object_effect_ptr> effects;
        int32_t object_u_i_d;
        int32_t quantity;
        
        int16_t id() const override
        { return 37; } 
        
        object_item(const int8_t & position, const int16_t & object_g_i_d, const int16_t & power_rate, const bool & over_max, const std::vector<object_effect_ptr> & effects, const int32_t & object_u_i_d, const int32_t & quantity)
        {
            _data << position;
            _data << object_g_i_d;
            _data << power_rate;
            _data << over_max;
            _data << static_cast<int16_t>(effects.size());
            for (auto && i : effects)
                _data << i->id() << i->buffer();
            _data << object_u_i_d;
            _data << quantity;
        }
        
        object_item(byte_buffer & data) : item { data }
        {
            data >> position;
            data >> object_g_i_d;
            data >> power_rate;
            data >> over_max;
            int16_t effects_size;
            data >> effects_size;
            effects.resize(effects_size);
            for (int16_t i = 0; i < effects_size; ++i)
            {
                int16_t p;
                data >> p;
                effects[i].reset(type_manager::get_object_effect(p, data));
            }
            data >> object_u_i_d;
            data >> quantity;
        }
    };
    
    using object_item_ptr = std::unique_ptr<object_item>;
}

#endif