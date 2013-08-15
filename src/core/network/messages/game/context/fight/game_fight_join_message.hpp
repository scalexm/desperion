//  Generated by desperion protocol_builder

#ifndef core_game_fight_join_message_hpp
#define core_game_fight_join_message_hpp

namespace network
{
    struct game_fight_join_message : dofus_unit
    {
        bool can_be_cancelled;
        bool can_say_ready;
        bool is_spectator;
        bool is_fight_started;
        int32_t time_max_before_fight_start;
        int8_t fight_type;
        
        int16_t id() const override
        { return 702; } 
        
        game_fight_join_message(const bool & can_be_cancelled, const bool & can_say_ready, const bool & is_spectator, const bool & is_fight_started, const int32_t & time_max_before_fight_start, const int8_t & fight_type)
        {
            int8_t flag = 0;
            set_bool_flag(flag, 0, can_be_cancelled);
            set_bool_flag(flag, 1, can_say_ready);
            set_bool_flag(flag, 2, is_spectator);
            set_bool_flag(flag, 3, is_fight_started);
            _data << flag;
            _data << time_max_before_fight_start;
            _data << fight_type;
        }
        
        game_fight_join_message(byte_buffer & data)
        {
            int8_t flag;
            data >> flag;
            can_be_cancelled = get_bool_flag(flag, 0);
            can_say_ready = get_bool_flag(flag, 1);
            is_spectator = get_bool_flag(flag, 2);
            is_fight_started = get_bool_flag(flag, 3);
            data >> time_max_before_fight_start;
            data >> fight_type;
        }
    };
}

#endif