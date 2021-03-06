//  Generated by desperion protocol_builder

#ifndef core_game_role_play_arena_fight_proposition_message_hpp
#define core_game_role_play_arena_fight_proposition_message_hpp

namespace protocol
{
    struct game_role_play_arena_fight_proposition_message : dofus_unit
    {
        int32_t fight_id;
        std::vector<int32_t> allies_id;
        int16_t duration;
        
        int16_t id() const override
        { return 6276; } 
        
        game_role_play_arena_fight_proposition_message(const int32_t & fight_id, const std::vector<int32_t> & allies_id, const int16_t & duration)
        {
            _data << fight_id;
            _data << static_cast<int16_t>(allies_id.size());
            for (auto && i : allies_id)
                _data << i;
            _data << duration;
        }
        
        game_role_play_arena_fight_proposition_message(byte_buffer & data)
        {
            data >> fight_id;
            int16_t allies_id_size;
            data >> allies_id_size;
            allies_id.resize(allies_id_size);
            for (int16_t i = 0; i < allies_id_size; ++i)
                data >> allies_id[i];
            data >> duration;
        }
    };
}

#endif
