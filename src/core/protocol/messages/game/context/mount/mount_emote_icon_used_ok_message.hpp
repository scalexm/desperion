//  Generated by desperion protocol_builder

#ifndef core_mount_emote_icon_used_ok_message_hpp
#define core_mount_emote_icon_used_ok_message_hpp

namespace protocol
{
    struct mount_emote_icon_used_ok_message : dofus_unit
    {
        int32_t mount_id;
        int8_t reaction_type;
        
        int16_t id() const override
        { return 5978; } 
        
        mount_emote_icon_used_ok_message(const int32_t & mount_id, const int8_t & reaction_type)
        {
            _data << mount_id;
            _data << reaction_type;
        }
        
        mount_emote_icon_used_ok_message(byte_buffer & data)
        {
            data >> mount_id;
            data >> reaction_type;
        }
    };
}

#endif
