//  Generated by desperion protocol_builder

#ifndef core_game_fight_a_i_informations_hpp
#define core_game_fight_a_i_informations_hpp

namespace network
{
    struct game_fight_a_i_informations : game_fight_fighter_informations
    {
        
        int16_t id() const override
        { return 151; } 
        
        game_fight_a_i_informations(const int8_t & team_id, const bool & alive, const game_fight_minimal_stats_ptr & stats, const int32_t & contextual_id, const entity_look_ptr & look, const entity_disposition_informations_ptr & disposition) : game_fight_fighter_informations { team_id,alive,stats,contextual_id,look,disposition }
        {
        }
        
        game_fight_a_i_informations(byte_buffer & data) : game_fight_fighter_informations { data }
        {
        }
    };
    
    using game_fight_a_i_informations_ptr = std::unique_ptr<game_fight_a_i_informations>;
}

#endif
