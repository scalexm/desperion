//  Generated by desperion protocol_builder

#ifndef core_exchange_start_ok_mount_with_out_paddock_message_hpp
#define core_exchange_start_ok_mount_with_out_paddock_message_hpp

namespace protocol
{
    struct exchange_start_ok_mount_with_out_paddock_message : dofus_unit
    {
        std::vector<mount_client_data_ptr> stabled_mounts_description;
        
        int16_t id() const override
        { return 5991; } 
        
        exchange_start_ok_mount_with_out_paddock_message(const std::vector<mount_client_data_ptr> & stabled_mounts_description)
        {
            _data << static_cast<int16_t>(stabled_mounts_description.size());
            for (auto && i : stabled_mounts_description)
                _data << i->buffer();
        }
        
        exchange_start_ok_mount_with_out_paddock_message(byte_buffer & data)
        {
            int16_t stabled_mounts_description_size;
            data >> stabled_mounts_description_size;
            stabled_mounts_description.resize(stabled_mounts_description_size);
            for (int16_t i = 0; i < stabled_mounts_description_size; ++i)
                stabled_mounts_description[i] = std::make_unique<mount_client_data>(data);
        }
    };
}

#endif
