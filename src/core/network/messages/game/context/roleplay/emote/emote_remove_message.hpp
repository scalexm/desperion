//  Generated by desperion protocol_builder

#ifndef core_emote_remove_message_hpp
#define core_emote_remove_message_hpp

namespace network
{
    struct emote_remove_message : dofus_unit
    {
        int8_t emote_id;
        
        int16_t id() const override
        { return 5687; } 
        
        emote_remove_message(const int8_t & emote_id)
        {
            _data << emote_id;
        }
        
        emote_remove_message(byte_buffer & data)
        {
            data >> emote_id;
        }
    };
}

#endif
