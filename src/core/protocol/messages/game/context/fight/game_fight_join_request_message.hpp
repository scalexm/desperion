//  Generated by desperion protocol_builder

#ifndef core_game_fight_join_request_message_hpp
#define core_game_fight_join_request_message_hpp

namespace protocol
{
    struct game_fight_join_request_message : dofus_unit
    {
        int32_t fighter_id;
        int32_t fight_id;
        
        int16_t id() const override
        { return 701; } 
        
        game_fight_join_request_message(const int32_t & fighter_id, const int32_t & fight_id)
        {
            _data << fighter_id;
            _data << fight_id;
        }
        
        game_fight_join_request_message(byte_buffer & data)
        {
            data >> fighter_id;
            data >> fight_id;
        }
    };
}

#endif
