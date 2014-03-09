//  Generated by desperion protocol_builder

#ifndef core_quest_start_request_message_hpp
#define core_quest_start_request_message_hpp

namespace protocol
{
    struct quest_start_request_message : dofus_unit
    {
        int16_t quest_id;
        
        int16_t id() const override
        { return 5643; } 
        
        quest_start_request_message(const int16_t & quest_id)
        {
            _data << quest_id;
        }
        
        quest_start_request_message(byte_buffer & data)
        {
            data >> quest_id;
        }
    };
}

#endif
