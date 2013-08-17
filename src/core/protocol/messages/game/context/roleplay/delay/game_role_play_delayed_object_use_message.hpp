//  Generated by desperion protocol_builder

#ifndef core_game_role_play_delayed_object_use_message_hpp
#define core_game_role_play_delayed_object_use_message_hpp

namespace network
{
    struct game_role_play_delayed_object_use_message : game_role_play_delayed_action_message
    {
        int16_t object_g_i_d;
        
        int16_t id() const override
        { return 6425; } 
        
        game_role_play_delayed_object_use_message(const int32_t & delayed_character_id, const int8_t & delay_type_id, const double & delay_end_time, const int16_t & object_g_i_d) : game_role_play_delayed_action_message { delayed_character_id,delay_type_id,delay_end_time }
        {
            _data << object_g_i_d;
        }
        
        game_role_play_delayed_object_use_message(byte_buffer & data) : game_role_play_delayed_action_message { data }
        {
            data >> object_g_i_d;
        }
    };
}

#endif