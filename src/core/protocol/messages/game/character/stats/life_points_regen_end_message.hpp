//  Generated by desperion protocol_builder

#ifndef core_life_points_regen_end_message_hpp
#define core_life_points_regen_end_message_hpp

namespace protocol
{
    struct life_points_regen_end_message : update_life_points_message
    {
        int32_t life_points_gained;
        
        int16_t id() const override
        { return 5686; } 
        
        life_points_regen_end_message(const int32_t & life_points, const int32_t & max_life_points, const int32_t & life_points_gained) : update_life_points_message { life_points,max_life_points }
        {
            _data << life_points_gained;
        }
        
        life_points_regen_end_message(byte_buffer & data) : update_life_points_message { data }
        {
            data >> life_points_gained;
        }
    };
}

#endif
