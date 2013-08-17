//  Generated by desperion protocol_builder

#ifndef core_update_self_agressable_status_message_hpp
#define core_update_self_agressable_status_message_hpp

namespace network
{
    struct update_self_agressable_status_message : dofus_unit
    {
        int8_t status;
        
        int16_t id() const override
        { return 6456; } 
        
        update_self_agressable_status_message(const int8_t & status)
        {
            _data << status;
        }
        
        update_self_agressable_status_message(byte_buffer & data)
        {
            data >> status;
        }
    };
}

#endif
