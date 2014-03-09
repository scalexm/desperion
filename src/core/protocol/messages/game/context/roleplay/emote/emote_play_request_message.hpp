//  Generated by desperion protocol_builder

#ifndef core_emote_play_request_message_hpp
#define core_emote_play_request_message_hpp

namespace protocol
{
    struct emote_play_request_message : dofus_unit
    {
        int8_t emote_id;
        
        int16_t id() const override
        { return 5685; } 
        
        emote_play_request_message(const int8_t & emote_id)
        {
            _data << emote_id;
        }
        
        emote_play_request_message(byte_buffer & data)
        {
            data >> emote_id;
        }
    };
}

#endif
