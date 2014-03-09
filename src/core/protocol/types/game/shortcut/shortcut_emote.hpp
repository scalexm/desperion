//  Generated by desperion protocol_builder

#ifndef core_shortcut_emote_hpp
#define core_shortcut_emote_hpp

namespace protocol
{
    struct shortcut_emote : shortcut
    {
        int8_t emote_id;
        
        int16_t id() const override
        { return 389; } 
        
        shortcut_emote(const int32_t & slot, const int8_t & emote_id) : shortcut { slot }
        {
            _data << emote_id;
        }
        
        shortcut_emote(byte_buffer & data) : shortcut { data }
        {
            data >> emote_id;
        }
    };
    
    using shortcut_emote_ptr = std::unique_ptr<shortcut_emote>;
}

#endif
