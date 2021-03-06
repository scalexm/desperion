//  Generated by desperion protocol_builder

#ifndef core_exchange_mount_stable_remove_message_hpp
#define core_exchange_mount_stable_remove_message_hpp

namespace protocol
{
    struct exchange_mount_stable_remove_message : dofus_unit
    {
        double mount_id;
        
        int16_t id() const override
        { return 5964; } 
        
        exchange_mount_stable_remove_message(const double & mount_id)
        {
            _data << mount_id;
        }
        
        exchange_mount_stable_remove_message(byte_buffer & data)
        {
            data >> mount_id;
        }
    };
}

#endif
