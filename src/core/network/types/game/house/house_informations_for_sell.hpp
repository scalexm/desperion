//  Generated by desperion protocol_builder

#ifndef core_house_informations_for_sell_hpp
#define core_house_informations_for_sell_hpp

namespace network
{
    struct house_informations_for_sell : dofus_unit
    {
        int32_t model_id;
        std::string owner_name;
        bool owner_connected;
        int16_t world_x;
        int16_t world_y;
        int16_t sub_area_id;
        int8_t nb_room;
        int8_t nb_chest;
        std::vector<int32_t> skill_list_ids;
        bool is_locked;
        int32_t price;
        
        int16_t id() const override
        { return 221; } 
        
        house_informations_for_sell(const int32_t & model_id, const std::string & owner_name, const bool & owner_connected, const int16_t & world_x, const int16_t & world_y, const int16_t & sub_area_id, const int8_t & nb_room, const int8_t & nb_chest, const std::vector<int32_t> & skill_list_ids, const bool & is_locked, const int32_t & price)
        {
            _data << model_id;
            _data << owner_name;
            _data << owner_connected;
            _data << world_x;
            _data << world_y;
            _data << sub_area_id;
            _data << nb_room;
            _data << nb_chest;
            _data << static_cast<int16_t>(skill_list_ids.size());
            for (auto && i : skill_list_ids)
                _data << i;
            _data << is_locked;
            _data << price;
        }
        
        house_informations_for_sell(byte_buffer & data)
        {
            data >> model_id;
            data >> owner_name;
            data >> owner_connected;
            data >> world_x;
            data >> world_y;
            data >> sub_area_id;
            data >> nb_room;
            data >> nb_chest;
            int16_t skill_list_ids_size;
            data >> skill_list_ids_size;
            skill_list_ids.resize(skill_list_ids_size);
            for (int16_t i = 0; i < skill_list_ids_size; ++i)
                data >> skill_list_ids[i];
            data >> is_locked;
            data >> price;
        }
    };
    
    using house_informations_for_sell_ptr = std::unique_ptr<house_informations_for_sell>;
}

#endif
