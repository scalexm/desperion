//  Generated by desperion protocol_builder

#ifndef core_abstract_fight_dispellable_effect_hpp
#define core_abstract_fight_dispellable_effect_hpp

namespace network
{
    struct abstract_fight_dispellable_effect : dofus_unit
    {
        int32_t uid;
        int32_t target_id;
        int16_t turn_duration;
        int8_t dispelable;
        int16_t spell_id;
        int32_t parent_boost_uid;
        
        int16_t id() const override
        { return 206; } 
        
        abstract_fight_dispellable_effect(const int32_t & uid, const int32_t & target_id, const int16_t & turn_duration, const int8_t & dispelable, const int16_t & spell_id, const int32_t & parent_boost_uid)
        {
            _data << uid;
            _data << target_id;
            _data << turn_duration;
            _data << dispelable;
            _data << spell_id;
            _data << parent_boost_uid;
        }
        
        abstract_fight_dispellable_effect(byte_buffer & data)
        {
            data >> uid;
            data >> target_id;
            data >> turn_duration;
            data >> dispelable;
            data >> spell_id;
            data >> parent_boost_uid;
        }
    };
    
    using abstract_fight_dispellable_effect_ptr = std::unique_ptr<abstract_fight_dispellable_effect>;
}

#endif
