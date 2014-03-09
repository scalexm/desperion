//  Generated by desperion protocol_builder

#ifndef core_exchange_handle_mount_stable_message_hpp
#define core_exchange_handle_mount_stable_message_hpp

namespace protocol
{
    struct exchange_handle_mount_stable_message : dofus_unit
    {
        int8_t action_type;
        int32_t ride_id;
        
        int16_t id() const override
        { return 5965; } 
        
        exchange_handle_mount_stable_message(const int8_t & action_type, const int32_t & ride_id)
        {
            _data << action_type;
            _data << ride_id;
        }
        
        exchange_handle_mount_stable_message(byte_buffer & data)
        {
            data >> action_type;
            data >> ride_id;
        }
    };
}

#endif
