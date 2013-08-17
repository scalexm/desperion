//  Generated by desperion protocol_builder

#ifndef core_living_object_dissociate_message_hpp
#define core_living_object_dissociate_message_hpp

namespace network
{
    struct living_object_dissociate_message : dofus_unit
    {
        int32_t living_u_i_d;
        int8_t living_position;
        
        int16_t id() const override
        { return 5723; } 
        
        living_object_dissociate_message(const int32_t & living_u_i_d, const int8_t & living_position)
        {
            _data << living_u_i_d;
            _data << living_position;
        }
        
        living_object_dissociate_message(byte_buffer & data)
        {
            data >> living_u_i_d;
            data >> living_position;
        }
    };
}

#endif
