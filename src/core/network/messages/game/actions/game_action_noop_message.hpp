//  Generated by desperion protocol_builder

#ifndef core_game_action_noop_message_hpp
#define core_game_action_noop_message_hpp

namespace network
{
    struct game_action_noop_message : dofus_unit
    {
        
        int16_t id() const override
        { return 1002; } 
        
        game_action_noop_message()
        {
        }
        
        game_action_noop_message(byte_buffer & data)
        {
        }
    };
}

#endif
