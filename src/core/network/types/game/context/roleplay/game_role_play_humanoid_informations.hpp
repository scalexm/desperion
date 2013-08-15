//  Generated by desperion protocol_builder

#ifndef core_game_role_play_humanoid_informations_hpp
#define core_game_role_play_humanoid_informations_hpp

namespace network
{
    struct game_role_play_humanoid_informations : game_role_play_named_actor_informations
    {
        human_informations_ptr humanoid_info;
        int32_t account_id;
        
        int16_t id() const override
        { return 159; } 
        
        game_role_play_humanoid_informations(const std::string & name, const int32_t & contextual_id, const entity_look_ptr & look, const entity_disposition_informations_ptr & disposition, const human_informations_ptr & humanoid_info, const int32_t & account_id) : game_role_play_named_actor_informations { name,contextual_id,look,disposition }
        {
            _data << humanoid_info->id() << humanoid_info->buffer();
            _data << account_id;
        }
        
        game_role_play_humanoid_informations(byte_buffer & data) : game_role_play_named_actor_informations { data }
        {
            int16_t humanoid_info_id;
            data >> humanoid_info_id;
            humanoid_info.reset(type_manager::get_human_informations(humanoid_info_id, data));
            data >> account_id;
        }
    };
    
    using game_role_play_humanoid_informations_ptr = std::unique_ptr<game_role_play_humanoid_informations>;
}

#endif
