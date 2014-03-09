//  Generated by desperion protocol_builder

#ifndef core_object_delete_message_hpp
#define core_object_delete_message_hpp

namespace protocol
{
    struct object_delete_message : dofus_unit
    {
        int32_t object_u_i_d;
        int32_t quantity;
        
        int16_t id() const override
        { return 3022; } 
        
        object_delete_message(const int32_t & object_u_i_d, const int32_t & quantity)
        {
            _data << object_u_i_d;
            _data << quantity;
        }
        
        object_delete_message(byte_buffer & data)
        {
            data >> object_u_i_d;
            data >> quantity;
        }
    };
}

#endif
