//  Generated by desperion protocol_builder

#ifndef core_startup_actions_objet_attribution_message_hpp
#define core_startup_actions_objet_attribution_message_hpp

namespace network
{
    struct startup_actions_objet_attribution_message : dofus_unit
    {
        int32_t action_id;
        int32_t character_id;
        
        int16_t id() const override
        { return 1303; } 
        
        startup_actions_objet_attribution_message(const int32_t & action_id, const int32_t & character_id)
        {
            _data << action_id;
            _data << character_id;
        }
        
        startup_actions_objet_attribution_message(byte_buffer & data)
        {
            data >> action_id;
            data >> character_id;
        }
    };
}

#endif
