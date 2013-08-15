//  Generated by desperion protocol_builder

#ifndef core_tax_collector_informations_hpp
#define core_tax_collector_informations_hpp

namespace network
{
    struct tax_collector_informations : dofus_unit
    {
        int32_t unique_id;
        int16_t firt_name_id;
        int16_t last_name_id;
        additional_tax_collector_informations_ptr additional_infos;
        int16_t world_x;
        int16_t world_y;
        int16_t sub_area_id;
        int8_t state;
        entity_look_ptr look;
        std::vector<tax_collector_complementary_informations_ptr> complements;
        
        int16_t id() const override
        { return 167; } 
        
        tax_collector_informations(const int32_t & unique_id, const int16_t & firt_name_id, const int16_t & last_name_id, const additional_tax_collector_informations_ptr & additional_infos, const int16_t & world_x, const int16_t & world_y, const int16_t & sub_area_id, const int8_t & state, const entity_look_ptr & look, const std::vector<tax_collector_complementary_informations_ptr> & complements)
        {
            _data << unique_id;
            _data << firt_name_id;
            _data << last_name_id;
            _data << additional_infos->buffer();
            _data << world_x;
            _data << world_y;
            _data << sub_area_id;
            _data << state;
            _data << look->buffer();
            _data << static_cast<int16_t>(complements.size());
            for (auto && i : complements)
                _data << i->id() << i->buffer();
        }
        
        tax_collector_informations(byte_buffer & data)
        {
            data >> unique_id;
            data >> firt_name_id;
            data >> last_name_id;
            additional_infos = std::make_unique<additional_tax_collector_informations>(data);
            data >> world_x;
            data >> world_y;
            data >> sub_area_id;
            data >> state;
            look = std::make_unique<entity_look>(data);
            int16_t complements_size;
            data >> complements_size;
            complements.resize(complements_size);
            for (int16_t i = 0; i < complements_size; ++i)
            {
                int16_t p;
                data >> p;
                complements[i].reset(type_manager::get_tax_collector_complementary_informations(p, data));
            }
        }
    };
    
    using tax_collector_informations_ptr = std::unique_ptr<tax_collector_informations>;
}

#endif
