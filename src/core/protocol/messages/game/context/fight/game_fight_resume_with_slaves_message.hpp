//  Generated by desperion protocol_builder

#ifndef core_game_fight_resume_with_slaves_message_hpp
#define core_game_fight_resume_with_slaves_message_hpp

namespace network
{
    struct game_fight_resume_with_slaves_message : game_fight_resume_message
    {
        std::vector<game_fight_resume_slave_info_ptr> slaves_info;
        
        int16_t id() const override
        { return 6215; } 
        
        game_fight_resume_with_slaves_message(const std::vector<game_fight_spell_cooldown_ptr> & spell_cooldowns, const int8_t & summon_count, const int8_t & bomb_count, const std::vector<fight_dispellable_effect_extended_informations_ptr> & effects, const std::vector<game_action_mark_ptr> & marks, const int16_t & game_turn, const std::vector<game_fight_resume_slave_info_ptr> & slaves_info) : game_fight_resume_message { spell_cooldowns,summon_count,bomb_count,effects,marks,game_turn }
        {
            _data << static_cast<int16_t>(slaves_info.size());
            for (auto && i : slaves_info)
                _data << i->buffer();
        }
        
        game_fight_resume_with_slaves_message(byte_buffer & data) : game_fight_resume_message { data }
        {
            int16_t slaves_info_size;
            data >> slaves_info_size;
            slaves_info.resize(slaves_info_size);
            for (int16_t i = 0; i < slaves_info_size; ++i)
                slaves_info[i] = std::make_unique<game_fight_resume_slave_info>(data);
        }
    };
}

#endif
