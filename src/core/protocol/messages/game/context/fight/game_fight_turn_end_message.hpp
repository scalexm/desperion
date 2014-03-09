//  Generated by desperion protocol_builder

#ifndef core_game_fight_turn_end_message_hpp
#define core_game_fight_turn_end_message_hpp

namespace protocol
{
    struct game_fight_turn_end_message : dofus_unit
    {
        int32_t id;
        
        int16_t id() const override
        { return 719; } 
        
        game_fight_turn_end_message(const int32_t & id)
        {
            _data << id;
        }
        
        game_fight_turn_end_message(byte_buffer & data)
        {
            data >> id;
        }
    };
}

#endif
