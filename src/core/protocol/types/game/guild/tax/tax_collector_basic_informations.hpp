//  Generated by desperion protocol_builder

#ifndef core_tax_collector_basic_informations_hpp
#define core_tax_collector_basic_informations_hpp

namespace protocol
{
    struct tax_collector_basic_informations : dofus_unit
    {
        int16_t first_name_id;
        int16_t last_name_id;
        int16_t world_x;
        int16_t world_y;
        int32_t map_id;
        int16_t sub_area_id;
        
        int16_t id() const override
        { return 96; } 
        
        tax_collector_basic_informations(const int16_t & first_name_id, const int16_t & last_name_id, const int16_t & world_x, const int16_t & world_y, const int32_t & map_id, const int16_t & sub_area_id)
        {
            _data << first_name_id;
            _data << last_name_id;
            _data << world_x;
            _data << world_y;
            _data << map_id;
            _data << sub_area_id;
        }
        
        tax_collector_basic_informations(byte_buffer & data)
        {
            data >> first_name_id;
            data >> last_name_id;
            data >> world_x;
            data >> world_y;
            data >> map_id;
            data >> sub_area_id;
        }
    };
    
    using tax_collector_basic_informations_ptr = std::unique_ptr<tax_collector_basic_informations>;
}

#endif
