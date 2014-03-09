//  Generated by desperion protocol_builder

#ifndef core_object_job_added_message_hpp
#define core_object_job_added_message_hpp

namespace protocol
{
    struct object_job_added_message : dofus_unit
    {
        int8_t job_id;
        
        int16_t id() const override
        { return 6014; } 
        
        object_job_added_message(const int8_t & job_id)
        {
            _data << job_id;
        }
        
        object_job_added_message(byte_buffer & data)
        {
            data >> job_id;
        }
    };
}

#endif
