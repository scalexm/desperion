//  Generated by desperion protocol_builder

#ifndef core_exchange_object_use_in_workshop_message_hpp
#define core_exchange_object_use_in_workshop_message_hpp

namespace protocol
{
    struct exchange_object_use_in_workshop_message : dofus_unit
    {
        int32_t object_u_i_d;
        int32_t quantity;
        
        int16_t id() const override
        { return 6004; } 
        
        exchange_object_use_in_workshop_message(const int32_t & object_u_i_d, const int32_t & quantity)
        {
            _data << object_u_i_d;
            _data << quantity;
        }
        
        exchange_object_use_in_workshop_message(byte_buffer & data)
        {
            data >> object_u_i_d;
            data >> quantity;
        }
    };
}

#endif
