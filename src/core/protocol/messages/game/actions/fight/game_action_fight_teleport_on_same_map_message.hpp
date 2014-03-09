//  Generated by desperion protocol_builder

#ifndef core_game_action_fight_teleport_on_same_map_message_hpp
#define core_game_action_fight_teleport_on_same_map_message_hpp

namespace protocol
{
    struct game_action_fight_teleport_on_same_map_message : abstract_game_action_message
    {
        int32_t target_id;
        int16_t cell_id;
        
        int16_t id() const override
        { return 5528; } 
        
        game_action_fight_teleport_on_same_map_message(const int16_t & action_id, const int32_t & source_id, const int32_t & target_id, const int16_t & cell_id) : abstract_game_action_message { action_id,source_id }
        {
            _data << target_id;
            _data << cell_id;
        }
        
        game_action_fight_teleport_on_same_map_message(byte_buffer & data) : abstract_game_action_message { data }
        {
            data >> target_id;
            data >> cell_id;
        }
    };
}

#endif
