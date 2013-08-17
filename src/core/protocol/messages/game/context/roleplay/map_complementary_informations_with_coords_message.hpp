//  Generated by desperion protocol_builder

#ifndef core_map_complementary_informations_with_coords_message_hpp
#define core_map_complementary_informations_with_coords_message_hpp

namespace network
{
    struct map_complementary_informations_with_coords_message : map_complementary_informations_data_message
    {
        int16_t world_x;
        int16_t world_y;
        
        int16_t id() const override
        { return 6268; } 
        
        map_complementary_informations_with_coords_message(const int16_t & sub_area_id, const int32_t & map_id, const std::vector<house_informations_ptr> & houses, const std::vector<game_role_play_actor_informations_ptr> & actors, const std::vector<interactive_element_ptr> & interactive_elements, const std::vector<stated_element_ptr> & stated_elements, const std::vector<map_obstacle_ptr> & obstacles, const std::vector<fight_common_informations_ptr> & fights, const int16_t & world_x, const int16_t & world_y) : map_complementary_informations_data_message { sub_area_id,map_id,houses,actors,interactive_elements,stated_elements,obstacles,fights }
        {
            _data << world_x;
            _data << world_y;
        }
        
        map_complementary_informations_with_coords_message(byte_buffer & data) : map_complementary_informations_data_message { data }
        {
            data >> world_x;
            data >> world_y;
        }
    };
}

#endif