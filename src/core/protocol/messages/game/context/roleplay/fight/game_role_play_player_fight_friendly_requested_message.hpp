//  Generated by desperion protocol_builder

#ifndef core_game_role_play_player_fight_friendly_requested_message_hpp
#define core_game_role_play_player_fight_friendly_requested_message_hpp

namespace protocol
{
    struct game_role_play_player_fight_friendly_requested_message : dofus_unit
    {
        int32_t fight_id;
        int32_t source_id;
        int32_t target_id;
        
        int16_t id() const override
        { return 5937; } 
        
        game_role_play_player_fight_friendly_requested_message(const int32_t & fight_id, const int32_t & source_id, const int32_t & target_id)
        {
            _data << fight_id;
            _data << source_id;
            _data << target_id;
        }
        
        game_role_play_player_fight_friendly_requested_message(byte_buffer & data)
        {
            data >> fight_id;
            data >> source_id;
            data >> target_id;
        }
    };
}

#endif
