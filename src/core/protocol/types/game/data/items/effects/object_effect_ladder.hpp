//  Generated by desperion protocol_builder

#ifndef core_object_effect_ladder_hpp
#define core_object_effect_ladder_hpp

namespace protocol
{
    struct object_effect_ladder : object_effect_creature
    {
        int32_t monster_count;
        
        int16_t id() const override
        { return 81; } 
        
        object_effect_ladder(const int16_t & monster_family_id, const int16_t & action_id, const int32_t & monster_count) : object_effect_creature { monster_family_id,action_id }
        {
            _data << monster_count;
        }
        
        object_effect_ladder(byte_buffer & data) : object_effect_creature { data }
        {
            data >> monster_count;
        }
    };
    
    using object_effect_ladder_ptr = std::unique_ptr<object_effect_ladder>;
}

#endif
