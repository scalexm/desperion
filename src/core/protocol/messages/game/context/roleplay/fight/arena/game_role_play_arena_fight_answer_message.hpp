//  Generated by desperion protocol_builder

#ifndef core_game_role_play_arena_fight_answer_message_hpp
#define core_game_role_play_arena_fight_answer_message_hpp

namespace protocol
{
    struct game_role_play_arena_fight_answer_message : dofus_unit
    {
        int32_t fight_id;
        bool accept;
        
        int16_t id() const override
        { return 6279; } 
        
        game_role_play_arena_fight_answer_message(const int32_t & fight_id, const bool & accept)
        {
            _data << fight_id;
            _data << accept;
        }
        
        game_role_play_arena_fight_answer_message(byte_buffer & data)
        {
            data >> fight_id;
            data >> accept;
        }
    };
}

#endif
