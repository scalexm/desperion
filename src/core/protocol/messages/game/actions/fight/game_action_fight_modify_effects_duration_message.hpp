//  Generated by desperion protocol_builder

#ifndef core_game_action_fight_modify_effects_duration_message_hpp
#define core_game_action_fight_modify_effects_duration_message_hpp

namespace network
{
    struct game_action_fight_modify_effects_duration_message : abstract_game_action_message
    {
        int32_t target_id;
        int16_t delta;
        
        int16_t id() const override
        { return 6304; } 
        
        game_action_fight_modify_effects_duration_message(const int16_t & action_id, const int32_t & source_id, const int32_t & target_id, const int16_t & delta) : abstract_game_action_message { action_id,source_id }
        {
            _data << target_id;
            _data << delta;
        }
        
        game_action_fight_modify_effects_duration_message(byte_buffer & data) : abstract_game_action_message { data }
        {
            data >> target_id;
            data >> delta;
        }
    };
}

#endif
