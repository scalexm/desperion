//  Generated by desperion protocol_builder

#ifndef d2fstream_map_position_hpp
#define d2fstream_map_position_hpp

namespace datacenter
{
    struct map_position : data_holder
    {
        int32_t id;
        int32_t pos_x;
        int32_t pos_y;
        bool outdoor;
        int32_t capabilities;
        int32_t name_id;
        std::vector<ambient_sound> sounds;
        int32_t sub_area_id;
        int32_t world_map;
        bool has_priority_on_worldmap;
        
        map_position() = default;
        
        map_position(const int32_t & id, const int32_t & pos_x, const int32_t & pos_y, const bool & outdoor, const int32_t & capabilities, const int32_t & name_id, const std::vector<ambient_sound> & sounds, const int32_t & sub_area_id, const int32_t & world_map, const bool & has_priority_on_worldmap) : id { id }, pos_x { pos_x }, pos_y { pos_y }, outdoor { outdoor }, capabilities { capabilities }, name_id { name_id }, sounds { sounds }, sub_area_id { sub_area_id }, world_map { world_map }, has_priority_on_worldmap { has_priority_on_worldmap }
        {
        }
        
        map_position(data_object && data)
        {
            acquire(id, data.second.at("id"));
            acquire(pos_x, data.second.at("posX"));
            acquire(pos_y, data.second.at("posY"));
            acquire(outdoor, data.second.at("outdoor"));
            acquire(capabilities, data.second.at("capabilities"));
            acquire(name_id, data.second.at("nameId"));
            acquire(sounds, data.second.at("sounds"));
            acquire(sub_area_id, data.second.at("subAreaId"));
            acquire(world_map, data.second.at("worldMap"));
            acquire(has_priority_on_worldmap, data.second.at("hasPriorityOnWorldmap"));
        }
        
        data_object to_d2o(const d2o_writer &);
    };

#ifdef d2fstream_d2o_writer_hpp
    data_object to_d2o(const d2o_writer & file)
    {
        data_object data;
        data.first = file.get_class_id_for_type<map_position>();
        release(id, data.second["id"], file);
        release(pos_x, data.second["posX"], file);
        release(pos_y, data.second["posY"], file);
        release(outdoor, data.second["outdoor"], file);
        release(capabilities, data.second["capabilities"], file);
        release(name_id, data.second["nameId"], file);
        release(sounds, data.second["sounds"], file);
        release(sub_area_id, data.second["subAreaId"], file);
        release(world_map, data.second["worldMap"], file);
        release(has_priority_on_worldmap, data.second["hasPriorityOnWorldmap"], file);
        return data;
    }
#endif
}
#endif