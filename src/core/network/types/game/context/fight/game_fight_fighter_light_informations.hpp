//  Generated by desperion protocol_builder

#ifndef core_game_fight_fighter_light_informations_hpp
#define core_game_fight_fighter_light_informations_hpp

namespace network
{
    struct game_fight_fighter_light_informations : dofus_unit
    {
        bool sex;
        bool alive;
        int32_t id;
        std::string name;
        int16_t level;
        int8_t breed;
        
        int16_t id() const override
        { return 413; } 
        
        game_fight_fighter_light_informations(const bool & sex, const bool & alive, const int32_t & id, const std::string & name, const int16_t & level, const int8_t & breed)
        {
            int8_t flag = 0;
            set_bool_flag(flag, 0, sex);
            set_bool_flag(flag, 1, alive);
            _data << flag;
            _data << id;
            _data << name;
            _data << level;
            _data << breed;
        }
        
        game_fight_fighter_light_informations(byte_buffer & data)
        {
            int8_t flag;
            data >> flag;
            sex = get_bool_flag(flag, 0);
            alive = get_bool_flag(flag, 1);
            data >> id;
            data >> name;
            data >> level;
            data >> breed;
        }
    };
    
    using game_fight_fighter_light_informations_ptr = std::unique_ptr<game_fight_fighter_light_informations>;
}

#endif
