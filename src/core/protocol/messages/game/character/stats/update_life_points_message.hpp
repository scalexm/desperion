//  Generated by desperion protocol_builder

#ifndef core_update_life_points_message_hpp
#define core_update_life_points_message_hpp

namespace protocol
{
    struct update_life_points_message : dofus_unit
    {
        int32_t life_points;
        int32_t max_life_points;
        
        int16_t id() const override
        { return 5658; } 
        
        update_life_points_message(const int32_t & life_points, const int32_t & max_life_points)
        {
            _data << life_points;
            _data << max_life_points;
        }
        
        update_life_points_message(byte_buffer & data)
        {
            data >> life_points;
            data >> max_life_points;
        }
    };
}

#endif
