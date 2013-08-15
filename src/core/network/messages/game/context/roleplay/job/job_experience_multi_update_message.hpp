//  Generated by desperion protocol_builder

#ifndef core_job_experience_multi_update_message_hpp
#define core_job_experience_multi_update_message_hpp

namespace network
{
    struct job_experience_multi_update_message : dofus_unit
    {
        std::vector<job_experience_ptr> experiences_update;
        
        int16_t id() const override
        { return 5809; } 
        
        job_experience_multi_update_message(const std::vector<job_experience_ptr> & experiences_update)
        {
            _data << static_cast<int16_t>(experiences_update.size());
            for (auto && i : experiences_update)
                _data << i->buffer();
        }
        
        job_experience_multi_update_message(byte_buffer & data)
        {
            int16_t experiences_update_size;
            data >> experiences_update_size;
            experiences_update.resize(experiences_update_size);
            for (int16_t i = 0; i < experiences_update_size; ++i)
                experiences_update[i] = std::make_unique<job_experience>(data);
        }
    };
}

#endif