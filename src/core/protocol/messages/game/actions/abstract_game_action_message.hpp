//  Generated by desperion protocol_builder

#ifndef core_abstract_game_action_message_hpp
#define core_abstract_game_action_message_hpp

namespace network
{
    struct abstract_game_action_message : dofus_unit
    {
        int16_t action_id;
        int32_t source_id;
        
        int16_t id() const override
        { return 1000; } 
        
        abstract_game_action_message(const int16_t & action_id, const int32_t & source_id)
        {
            _data << action_id;
            _data << source_id;
        }
        
        abstract_game_action_message(byte_buffer & data)
        {
            data >> action_id;
            data >> source_id;
        }
    };
}

#endif
