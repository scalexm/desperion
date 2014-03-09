//  Generated by desperion protocol_builder

#ifndef core_job_description_message_hpp
#define core_job_description_message_hpp

namespace protocol
{
    struct job_description_message : dofus_unit
    {
        std::vector<job_description_ptr> jobs_description;
        
        int16_t id() const override
        { return 5655; } 
        
        job_description_message(const std::vector<job_description_ptr> & jobs_description)
        {
            _data << static_cast<int16_t>(jobs_description.size());
            for (auto && i : jobs_description)
                _data << i->buffer();
        }
        
        job_description_message(byte_buffer & data)
        {
            int16_t jobs_description_size;
            data >> jobs_description_size;
            jobs_description.resize(jobs_description_size);
            for (int16_t i = 0; i < jobs_description_size; ++i)
                jobs_description[i] = std::make_unique<job_description>(data);
        }
    };
}

#endif
