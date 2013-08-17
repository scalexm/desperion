//  Generated by desperion protocol_builder

#ifndef core_fight_temporary_spell_boost_effect_hpp
#define core_fight_temporary_spell_boost_effect_hpp

namespace network
{
    struct fight_temporary_spell_boost_effect : fight_temporary_boost_effect
    {
        int16_t boosted_spell_id;
        
        int16_t id() const override
        { return 207; } 
        
        fight_temporary_spell_boost_effect(const int16_t & delta, const int32_t & uid, const int32_t & target_id, const int16_t & turn_duration, const int8_t & dispelable, const int16_t & spell_id, const int32_t & parent_boost_uid, const int16_t & boosted_spell_id) : fight_temporary_boost_effect { delta,uid,target_id,turn_duration,dispelable,spell_id,parent_boost_uid }
        {
            _data << boosted_spell_id;
        }
        
        fight_temporary_spell_boost_effect(byte_buffer & data) : fight_temporary_boost_effect { data }
        {
            data >> boosted_spell_id;
        }
    };
    
    using fight_temporary_spell_boost_effect_ptr = std::unique_ptr<fight_temporary_spell_boost_effect>;
}

#endif
