//  Generated by desperion protocol_builder

#ifndef core_friend_spouse_online_informations_hpp
#define core_friend_spouse_online_informations_hpp

namespace protocol
{
    struct friend_spouse_online_informations : friend_spouse_informations
    {
        bool in_fight;
        bool follow_spouse;
        int32_t map_id;
        int16_t sub_area_id;
        
        int16_t id() const override
        { return 93; } 
        
        friend_spouse_online_informations(const int32_t & spouse_account_id, const int32_t & spouse_id, const std::string & spouse_name, const int8_t & spouse_level, const int8_t & breed, const int8_t & sex, const entity_look_ptr & spouse_entity_look, const basic_guild_informations_ptr & guild_info, const int8_t & alignment_side, const bool & in_fight, const bool & follow_spouse, const int32_t & map_id, const int16_t & sub_area_id) : friend_spouse_informations { spouse_account_id,spouse_id,spouse_name,spouse_level,breed,sex,spouse_entity_look,guild_info,alignment_side }
        {
            int8_t flag = 0;
            set_bool_flag(flag, 0, in_fight);
            set_bool_flag(flag, 1, follow_spouse);
            _data << flag;
            _data << map_id;
            _data << sub_area_id;
        }
        
        friend_spouse_online_informations(byte_buffer & data) : friend_spouse_informations { data }
        {
            int8_t flag;
            data >> flag;
            in_fight = get_bool_flag(flag, 0);
            follow_spouse = get_bool_flag(flag, 1);
            data >> map_id;
            data >> sub_area_id;
        }
    };
    
    using friend_spouse_online_informations_ptr = std::unique_ptr<friend_spouse_online_informations>;
}

#endif
