//  Generated by desperion protocol_builder

#ifndef core_game_context_create_request_message_hpp
#define core_game_context_create_request_message_hpp

namespace protocol
{
    struct game_context_create_request_message : dofus_unit
    {
        
        int16_t id() const override
        { return 250; } 
        
        game_context_create_request_message()
        {
        }
        
        game_context_create_request_message(byte_buffer & data)
        {
        }
    };
}

#endif
