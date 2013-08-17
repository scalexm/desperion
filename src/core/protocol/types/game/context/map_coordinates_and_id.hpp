//  Generated by desperion protocol_builder

#ifndef core_map_coordinates_and_id_hpp
#define core_map_coordinates_and_id_hpp

namespace network
{
    struct map_coordinates_and_id : map_coordinates
    {
        int32_t map_id;
        
        int16_t id() const override
        { return 392; } 
        
        map_coordinates_and_id(const int16_t & world_x, const int16_t & world_y, const int32_t & map_id) : map_coordinates { world_x,world_y }
        {
            _data << map_id;
        }
        
        map_coordinates_and_id(byte_buffer & data) : map_coordinates { data }
        {
            data >> map_id;
        }
    };
    
    using map_coordinates_and_id_ptr = std::unique_ptr<map_coordinates_and_id>;
}

#endif