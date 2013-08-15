//  Generated by desperion protocol_builder

#ifndef core_interactive_used_message_hpp
#define core_interactive_used_message_hpp

namespace network
{
    struct interactive_used_message : dofus_unit
    {
        int32_t entity_id;
        int32_t elem_id;
        int16_t skill_id;
        int16_t duration;
        
        int16_t id() const override
        { return 5745; } 
        
        interactive_used_message(const int32_t & entity_id, const int32_t & elem_id, const int16_t & skill_id, const int16_t & duration)
        {
            _data << entity_id;
            _data << elem_id;
            _data << skill_id;
            _data << duration;
        }
        
        interactive_used_message(byte_buffer & data)
        {
            data >> entity_id;
            data >> elem_id;
            data >> skill_id;
            data >> duration;
        }
    };
}

#endif
