//  Generated by desperion protocol_builder

#ifndef core_alliance_facts_request_message_hpp
#define core_alliance_facts_request_message_hpp

namespace network
{
    struct alliance_facts_request_message : dofus_unit
    {
        int32_t alliance_id;
        
        int16_t id() const override
        { return 6409; } 
        
        alliance_facts_request_message(const int32_t & alliance_id)
        {
            _data << alliance_id;
        }
        
        alliance_facts_request_message(byte_buffer & data)
        {
            data >> alliance_id;
        }
    };
}

#endif
