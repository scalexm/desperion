//  Generated by desperion protocol_builder

#ifndef core_object_effect_min_max_hpp
#define core_object_effect_min_max_hpp

namespace network
{
    struct object_effect_min_max : object_effect
    {
        int16_t min;
        int16_t max;
        
        int16_t id() const override
        { return 82; } 
        
        object_effect_min_max(const int16_t & action_id, const int16_t & min, const int16_t & max) : object_effect { action_id }
        {
            _data << min;
            _data << max;
        }
        
        object_effect_min_max(byte_buffer & data) : object_effect { data }
        {
            data >> min;
            data >> max;
        }
    };
    
    using object_effect_min_max_ptr = std::unique_ptr<object_effect_min_max>;
}

#endif
