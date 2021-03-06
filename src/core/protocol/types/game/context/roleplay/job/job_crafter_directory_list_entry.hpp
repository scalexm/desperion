//  Generated by desperion protocol_builder

#ifndef core_job_crafter_directory_list_entry_hpp
#define core_job_crafter_directory_list_entry_hpp

namespace protocol
{
    struct job_crafter_directory_list_entry : dofus_unit
    {
        job_crafter_directory_entry_player_info_ptr player_info;
        job_crafter_directory_entry_job_info_ptr job_info;
        
        int16_t id() const override
        { return 196; } 
        
        job_crafter_directory_list_entry(const job_crafter_directory_entry_player_info_ptr & player_info, const job_crafter_directory_entry_job_info_ptr & job_info)
        {
            _data << player_info->buffer();
            _data << job_info->buffer();
        }
        
        job_crafter_directory_list_entry(byte_buffer & data)
        {
            player_info = std::make_unique<job_crafter_directory_entry_player_info>(data);
            job_info = std::make_unique<job_crafter_directory_entry_job_info>(data);
        }
    };
    
    using job_crafter_directory_list_entry_ptr = std::unique_ptr<job_crafter_directory_list_entry>;
}

#endif
