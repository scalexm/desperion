//  Generated by desperion protocol_builder

#ifndef d2fstream_monster_grade_hpp
#define d2fstream_monster_grade_hpp

namespace datacenter
{
    struct monster_grade : data_holder
    {
        int32_t grade;
        int32_t monster_id;
        int32_t level;
        int32_t pa_dodge;
        int32_t pm_dodge;
        int32_t wisdom;
        int32_t earth_resistance;
        int32_t air_resistance;
        int32_t fire_resistance;
        int32_t water_resistance;
        int32_t neutral_resistance;
        int32_t grade_xp;
        int32_t life_points;
        int32_t action_points;
        int32_t movement_points;
        
        monster_grade() = default;
        
        monster_grade(const int32_t & grade, const int32_t & monster_id, const int32_t & level, const int32_t & pa_dodge, const int32_t & pm_dodge, const int32_t & wisdom, const int32_t & earth_resistance, const int32_t & air_resistance, const int32_t & fire_resistance, const int32_t & water_resistance, const int32_t & neutral_resistance, const int32_t & grade_xp, const int32_t & life_points, const int32_t & action_points, const int32_t & movement_points) : grade { grade }, monster_id { monster_id }, level { level }, pa_dodge { pa_dodge }, pm_dodge { pm_dodge }, wisdom { wisdom }, earth_resistance { earth_resistance }, air_resistance { air_resistance }, fire_resistance { fire_resistance }, water_resistance { water_resistance }, neutral_resistance { neutral_resistance }, grade_xp { grade_xp }, life_points { life_points }, action_points { action_points }, movement_points { movement_points }
        {
        }
        
        monster_grade(data_object && data)
        {
            acquire(grade, data.second.at("grade"));
            acquire(monster_id, data.second.at("monsterId"));
            acquire(level, data.second.at("level"));
            acquire(pa_dodge, data.second.at("paDodge"));
            acquire(pm_dodge, data.second.at("pmDodge"));
            acquire(wisdom, data.second.at("wisdom"));
            acquire(earth_resistance, data.second.at("earthResistance"));
            acquire(air_resistance, data.second.at("airResistance"));
            acquire(fire_resistance, data.second.at("fireResistance"));
            acquire(water_resistance, data.second.at("waterResistance"));
            acquire(neutral_resistance, data.second.at("neutralResistance"));
            acquire(grade_xp, data.second.at("gradeXp"));
            acquire(life_points, data.second.at("lifePoints"));
            acquire(action_points, data.second.at("actionPoints"));
            acquire(movement_points, data.second.at("movementPoints"));
        }
        
        data_object to_d2o(const d2o_writer &);
    };

#ifdef d2fstream_d2o_writer_hpp
    data_object to_d2o(const d2o_writer & file)
    {
        data_object data;
        data.first = file.get_class_id_for_type<monster_grade>();
        release(grade, data.second["grade"], file);
        release(monster_id, data.second["monsterId"], file);
        release(level, data.second["level"], file);
        release(pa_dodge, data.second["paDodge"], file);
        release(pm_dodge, data.second["pmDodge"], file);
        release(wisdom, data.second["wisdom"], file);
        release(earth_resistance, data.second["earthResistance"], file);
        release(air_resistance, data.second["airResistance"], file);
        release(fire_resistance, data.second["fireResistance"], file);
        release(water_resistance, data.second["waterResistance"], file);
        release(neutral_resistance, data.second["neutralResistance"], file);
        release(grade_xp, data.second["gradeXp"], file);
        release(life_points, data.second["lifePoints"], file);
        release(action_points, data.second["actionPoints"], file);
        release(movement_points, data.second["movementPoints"], file);
        return data;
    }
#endif
}
#endif