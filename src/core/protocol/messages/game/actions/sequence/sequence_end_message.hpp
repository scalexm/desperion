//  Generated by desperion protocol_builder

#ifndef core_sequence_end_message_hpp
#define core_sequence_end_message_hpp

namespace protocol
{
    struct sequence_end_message : dofus_unit
    {
        int16_t action_id;
        int32_t author_id;
        int8_t sequence_type;
        
        int16_t id() const override
        { return 956; } 
        
        sequence_end_message(const int16_t & action_id, const int32_t & author_id, const int8_t & sequence_type)
        {
            _data << action_id;
            _data << author_id;
            _data << sequence_type;
        }
        
        sequence_end_message(byte_buffer & data)
        {
            data >> action_id;
            data >> author_id;
            data >> sequence_type;
        }
    };
}

#endif
