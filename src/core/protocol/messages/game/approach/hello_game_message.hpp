//  Generated by desperion protocol_builder

#ifndef core_hello_game_message_hpp
#define core_hello_game_message_hpp

namespace network
{
    struct hello_game_message : dofus_unit
    {
        
        int16_t id() const override
        { return 101; } 
        
        hello_game_message()
        {
        }
        
        hello_game_message(byte_buffer & data)
        {
        }
    };
}

#endif