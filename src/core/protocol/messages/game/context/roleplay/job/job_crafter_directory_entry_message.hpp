//  Generated by desperion protocol_builder

#ifndef core_job_crafter_directory_entry_message_hpp
#define core_job_crafter_directory_entry_message_hpp

namespace protocol
{
    struct job_crafter_directory_entry_message : dofus_unit
    {
        job_crafter_directory_entry_player_info_ptr player_info;
        std::vector<job_crafter_directory_entry_job_info_ptr> job_info_list;
        entity_look_ptr player_look;
        
        int16_t id() const override
        { return 6044; } 
        
        job_crafter_directory_entry_message(const job_crafter_directory_entry_player_info_ptr & player_info, const std::vector<job_crafter_directory_entry_job_info_ptr> & job_info_list, const entity_look_ptr & player_look)
        {
            _data << player_info->buffer();
            _data << static_cast<int16_t>(job_info_list.size());
            for (auto && i : job_info_list)
                _data << i->buffer();
            _data << player_look->buffer();
        }
        
        job_crafter_directory_entry_message(byte_buffer & data)
        {
            player_info = std::make_unique<job_crafter_directory_entry_player_info>(data);
            int16_t job_info_list_size;
            data >> job_info_list_size;
            job_info_list.resize(job_info_list_size);
            for (int16_t i = 0; i < job_info_list_size; ++i)
                job_info_list[i] = std::make_unique<job_crafter_directory_entry_job_info>(data);
            player_look = std::make_unique<entity_look>(data);
        }
    };
}

#endif
