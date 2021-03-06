//  Generated by desperion protocol_builder

#ifndef core_game_action_fight_state_change_message_hpp
#define core_game_action_fight_state_change_message_hpp

namespace protocol
{
    struct game_action_fight_state_change_message : abstract_game_action_message
    {
        int32_t target_id;
        int16_t state_id;
        bool active;
        
        int16_t id() const override
        { return 5569; } 
        
        game_action_fight_state_change_message(const int16_t & action_id, const int32_t & source_id, const int32_t & target_id, const int16_t & state_id, const bool & active) : abstract_game_action_message { action_id,source_id }
        {
            _data << target_id;
            _data << state_id;
            _data << active;
        }
        
        game_action_fight_state_change_message(byte_buffer & data) : abstract_game_action_message { data }
        {
            data >> target_id;
            data >> state_id;
            data >> active;
        }
    };
}

#endif
