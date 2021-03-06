//  Generated by desperion protocol_builder

#ifndef core_game_fight_character_informations_hpp
#define core_game_fight_character_informations_hpp

namespace protocol
{
    struct game_fight_character_informations : game_fight_fighter_named_informations
    {
        int16_t level;
        actor_alignment_informations_ptr alignment_infos;
        int8_t breed;
        
        int16_t id() const override
        { return 46; } 
        
        game_fight_character_informations(const std::string & name, const player_status_ptr & status, const int8_t & team_id, const bool & alive, const game_fight_minimal_stats_ptr & stats, const int32_t & contextual_id, const entity_look_ptr & look, const entity_disposition_informations_ptr & disposition, const int16_t & level, const actor_alignment_informations_ptr & alignment_infos, const int8_t & breed) : game_fight_fighter_named_informations { name,status,team_id,alive,stats,contextual_id,look,disposition }
        {
            _data << level;
            _data << alignment_infos->buffer();
            _data << breed;
        }
        
        game_fight_character_informations(byte_buffer & data) : game_fight_fighter_named_informations { data }
        {
            data >> level;
            alignment_infos = std::make_unique<actor_alignment_informations>(data);
            data >> breed;
        }
    };
    
    using game_fight_character_informations_ptr = std::unique_ptr<game_fight_character_informations>;
}

#endif
