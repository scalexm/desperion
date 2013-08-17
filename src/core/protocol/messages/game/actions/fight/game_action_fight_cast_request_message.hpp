//  Generated by desperion protocol_builder

#ifndef core_game_action_fight_cast_request_message_hpp
#define core_game_action_fight_cast_request_message_hpp

namespace network
{
    struct game_action_fight_cast_request_message : dofus_unit
    {
        int16_t spell_id;
        int16_t cell_id;
        
        int16_t id() const override
        { return 1005; } 
        
        game_action_fight_cast_request_message(const int16_t & spell_id, const int16_t & cell_id)
        {
            _data << spell_id;
            _data << cell_id;
        }
        
        game_action_fight_cast_request_message(byte_buffer & data)
        {
            data >> spell_id;
            data >> cell_id;
        }
    };
}

#endif
