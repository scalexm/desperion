//  Generated by desperion protocol_builder

#ifndef core_game_fight_turn_finish_message_hpp
#define core_game_fight_turn_finish_message_hpp

namespace network
{
    struct game_fight_turn_finish_message : dofus_unit
    {
        
        int16_t id() const override
        { return 718; } 
        
        game_fight_turn_finish_message()
        {
        }
        
        game_fight_turn_finish_message(byte_buffer & data)
        {
        }
    };
}

#endif