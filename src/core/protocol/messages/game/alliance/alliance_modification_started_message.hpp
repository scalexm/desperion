//  Generated by desperion protocol_builder

#ifndef core_alliance_modification_started_message_hpp
#define core_alliance_modification_started_message_hpp

namespace protocol
{
    struct alliance_modification_started_message : dofus_unit
    {
        bool can_change_name;
        bool can_change_tag;
        bool can_change_emblem;
        
        int16_t id() const override
        { return 6444; } 
        
        alliance_modification_started_message(const bool & can_change_name, const bool & can_change_tag, const bool & can_change_emblem)
        {
            int8_t flag = 0;
            set_bool_flag(flag, 0, can_change_name);
            set_bool_flag(flag, 1, can_change_tag);
            set_bool_flag(flag, 2, can_change_emblem);
            _data << flag;
        }
        
        alliance_modification_started_message(byte_buffer & data)
        {
            int8_t flag;
            data >> flag;
            can_change_name = get_bool_flag(flag, 0);
            can_change_tag = get_bool_flag(flag, 1);
            can_change_emblem = get_bool_flag(flag, 2);
        }
    };
}

#endif
