//  Generated by desperion protocol_builder

#ifndef core_mood_smiley_update_message_hpp
#define core_mood_smiley_update_message_hpp

namespace network
{
    struct mood_smiley_update_message : dofus_unit
    {
        int32_t account_id;
        int32_t player_id;
        int8_t smiley_id;
        
        int16_t id() const override
        { return 6388; } 
        
        mood_smiley_update_message(const int32_t & account_id, const int32_t & player_id, const int8_t & smiley_id)
        {
            _data << account_id;
            _data << player_id;
            _data << smiley_id;
        }
        
        mood_smiley_update_message(byte_buffer & data)
        {
            data >> account_id;
            data >> player_id;
            data >> smiley_id;
        }
    };
}

#endif
