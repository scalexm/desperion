//  Generated by desperion protocol_builder

#ifndef core_character_minimal_plus_look_informations_hpp
#define core_character_minimal_plus_look_informations_hpp

namespace protocol
{
    struct character_minimal_plus_look_informations : character_minimal_informations
    {
        entity_look_ptr entity_look;
        
        int16_t id() const override
        { return 163; } 
        
        character_minimal_plus_look_informations(const int8_t & level, const std::string & name, const int32_t & id, const entity_look_ptr & entity_look) : character_minimal_informations { level,name,id }
        {
            _data << entity_look->buffer();
        }
        
        character_minimal_plus_look_informations(byte_buffer & data) : character_minimal_informations { data }
        {
            entity_look = std::make_unique<entity_look>(data);
        }
    };
    
    using character_minimal_plus_look_informations_ptr = std::unique_ptr<character_minimal_plus_look_informations>;
}

#endif
