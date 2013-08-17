//  Generated by desperion protocol_builder

#ifndef core_living_object_change_skin_request_message_hpp
#define core_living_object_change_skin_request_message_hpp

namespace network
{
    struct living_object_change_skin_request_message : dofus_unit
    {
        int32_t living_u_i_d;
        int8_t living_position;
        int32_t skin_id;
        
        int16_t id() const override
        { return 5725; } 
        
        living_object_change_skin_request_message(const int32_t & living_u_i_d, const int8_t & living_position, const int32_t & skin_id)
        {
            _data << living_u_i_d;
            _data << living_position;
            _data << skin_id;
        }
        
        living_object_change_skin_request_message(byte_buffer & data)
        {
            data >> living_u_i_d;
            data >> living_position;
            data >> skin_id;
        }
    };
}

#endif
