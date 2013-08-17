//  Generated by desperion protocol_builder

#ifndef core_character_minimal_alliance_informations_hpp
#define core_character_minimal_alliance_informations_hpp

namespace network
{
    struct character_minimal_alliance_informations : character_minimal_guild_informations
    {
        basic_alliance_informations_ptr alliance;
        
        int16_t id() const override
        { return 444; } 
        
        character_minimal_alliance_informations(const basic_guild_informations_ptr & guild, const entity_look_ptr & entity_look, const int8_t & level, const std::string & name, const int32_t & id, const basic_alliance_informations_ptr & alliance) : character_minimal_guild_informations { guild,entity_look,level,name,id }
        {
            _data << alliance->buffer();
        }
        
        character_minimal_alliance_informations(byte_buffer & data) : character_minimal_guild_informations { data }
        {
            alliance = std::make_unique<basic_alliance_informations>(data);
        }
    };
    
    using character_minimal_alliance_informations_ptr = std::unique_ptr<character_minimal_alliance_informations>;
}

#endif
