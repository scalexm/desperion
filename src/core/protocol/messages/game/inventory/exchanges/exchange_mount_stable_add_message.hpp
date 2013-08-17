//  Generated by desperion protocol_builder

#ifndef core_exchange_mount_stable_add_message_hpp
#define core_exchange_mount_stable_add_message_hpp

namespace network
{
    struct exchange_mount_stable_add_message : dofus_unit
    {
        mount_client_data_ptr mount_description;
        
        int16_t id() const override
        { return 5971; } 
        
        exchange_mount_stable_add_message(const mount_client_data_ptr & mount_description)
        {
            _data << mount_description->buffer();
        }
        
        exchange_mount_stable_add_message(byte_buffer & data)
        {
            mount_description = std::make_unique<mount_client_data>(data);
        }
    };
}

#endif
