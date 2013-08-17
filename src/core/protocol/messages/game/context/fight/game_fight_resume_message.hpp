//  Generated by desperion protocol_builder

#ifndef core_game_fight_resume_message_hpp
#define core_game_fight_resume_message_hpp

namespace network
{
    struct game_fight_resume_message : game_fight_spectate_message
    {
        std::vector<game_fight_spell_cooldown_ptr> spell_cooldowns;
        int8_t summon_count;
        int8_t bomb_count;
        
        int16_t id() const override
        { return 6067; } 
        
        game_fight_resume_message(const std::vector<fight_dispellable_effect_extended_informations_ptr> & effects, const std::vector<game_action_mark_ptr> & marks, const int16_t & game_turn, const std::vector<game_fight_spell_cooldown_ptr> & spell_cooldowns, const int8_t & summon_count, const int8_t & bomb_count) : game_fight_spectate_message { effects,marks,game_turn }
        {
            _data << static_cast<int16_t>(spell_cooldowns.size());
            for (auto && i : spell_cooldowns)
                _data << i->buffer();
            _data << summon_count;
            _data << bomb_count;
        }
        
        game_fight_resume_message(byte_buffer & data) : game_fight_spectate_message { data }
        {
            int16_t spell_cooldowns_size;
            data >> spell_cooldowns_size;
            spell_cooldowns.resize(spell_cooldowns_size);
            for (int16_t i = 0; i < spell_cooldowns_size; ++i)
                spell_cooldowns[i] = std::make_unique<game_fight_spell_cooldown>(data);
            data >> summon_count;
            data >> bomb_count;
        }
    };
}

#endif
