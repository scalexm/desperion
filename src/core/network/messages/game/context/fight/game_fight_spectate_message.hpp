//  Generated by desperion protocol_builder

#ifndef core_game_fight_spectate_message_hpp
#define core_game_fight_spectate_message_hpp

namespace network
{
    struct game_fight_spectate_message : dofus_unit
    {
        std::vector<fight_dispellable_effect_extended_informations_ptr> effects;
        std::vector<game_action_mark_ptr> marks;
        int16_t game_turn;
        
        int16_t id() const override
        { return 6069; } 
        
        game_fight_spectate_message(const std::vector<fight_dispellable_effect_extended_informations_ptr> & effects, const std::vector<game_action_mark_ptr> & marks, const int16_t & game_turn)
        {
            _data << static_cast<int16_t>(effects.size());
            for (auto && i : effects)
                _data << i->buffer();
            _data << static_cast<int16_t>(marks.size());
            for (auto && i : marks)
                _data << i->buffer();
            _data << game_turn;
        }
        
        game_fight_spectate_message(byte_buffer & data)
        {
            int16_t effects_size;
            data >> effects_size;
            effects.resize(effects_size);
            for (int16_t i = 0; i < effects_size; ++i)
                effects[i] = std::make_unique<fight_dispellable_effect_extended_informations>(data);
            int16_t marks_size;
            data >> marks_size;
            marks.resize(marks_size);
            for (int16_t i = 0; i < marks_size; ++i)
                marks[i] = std::make_unique<game_action_mark>(data);
            data >> game_turn;
        }
    };
}

#endif
