//  Generated by desperion protocol_builder

#ifndef core_emote_play_message_hpp
#define core_emote_play_message_hpp

namespace protocol
{
    struct emote_play_message : emote_play_abstract_message
    {
        int32_t actor_id;
        int32_t account_id;
        
        int16_t id() const override
        { return 5683; } 
        
        emote_play_message(const int8_t & emote_id, const double & emote_start_time, const int32_t & actor_id, const int32_t & account_id) : emote_play_abstract_message { emote_id,emote_start_time }
        {
            _data << actor_id;
            _data << account_id;
        }
        
        emote_play_message(byte_buffer & data) : emote_play_abstract_message { data }
        {
            data >> actor_id;
            data >> account_id;
        }
    };
}

#endif
