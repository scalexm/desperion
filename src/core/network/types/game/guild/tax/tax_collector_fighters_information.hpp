//  Generated by desperion protocol_builder

#ifndef core_tax_collector_fighters_information_hpp
#define core_tax_collector_fighters_information_hpp

namespace network
{
    struct tax_collector_fighters_information : dofus_unit
    {
        int32_t collector_id;
        std::vector<character_minimal_plus_look_informations_ptr> ally_characters_informations;
        std::vector<character_minimal_plus_look_informations_ptr> enemy_characters_informations;
        
        int16_t id() const override
        { return 169; } 
        
        tax_collector_fighters_information(const int32_t & collector_id, const std::vector<character_minimal_plus_look_informations_ptr> & ally_characters_informations, const std::vector<character_minimal_plus_look_informations_ptr> & enemy_characters_informations)
        {
            _data << collector_id;
            _data << static_cast<int16_t>(ally_characters_informations.size());
            for (auto && i : ally_characters_informations)
                _data << i->id() << i->buffer();
            _data << static_cast<int16_t>(enemy_characters_informations.size());
            for (auto && i : enemy_characters_informations)
                _data << i->id() << i->buffer();
        }
        
        tax_collector_fighters_information(byte_buffer & data)
        {
            data >> collector_id;
            int16_t ally_characters_informations_size;
            data >> ally_characters_informations_size;
            ally_characters_informations.resize(ally_characters_informations_size);
            for (int16_t i = 0; i < ally_characters_informations_size; ++i)
            {
                int16_t p;
                data >> p;
                ally_characters_informations[i].reset(type_manager::get_character_minimal_plus_look_informations(p, data));
            }
            int16_t enemy_characters_informations_size;
            data >> enemy_characters_informations_size;
            enemy_characters_informations.resize(enemy_characters_informations_size);
            for (int16_t i = 0; i < enemy_characters_informations_size; ++i)
            {
                int16_t p;
                data >> p;
                enemy_characters_informations[i].reset(type_manager::get_character_minimal_plus_look_informations(p, data));
            }
        }
    };
    
    using tax_collector_fighters_information_ptr = std::unique_ptr<tax_collector_fighters_information>;
}

#endif
