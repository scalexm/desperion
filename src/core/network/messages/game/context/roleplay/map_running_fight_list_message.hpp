//  Generated by desperion protocol_builder

#ifndef core_map_running_fight_list_message_hpp
#define core_map_running_fight_list_message_hpp

namespace network
{
    struct map_running_fight_list_message : dofus_unit
    {
        std::vector<fight_external_informations_ptr> fights;
        
        int16_t id() const override
        { return 5743; } 
        
        map_running_fight_list_message(const std::vector<fight_external_informations_ptr> & fights)
        {
            _data << static_cast<int16_t>(fights.size());
            for (auto && i : fights)
                _data << i->buffer();
        }
        
        map_running_fight_list_message(byte_buffer & data)
        {
            int16_t fights_size;
            data >> fights_size;
            fights.resize(fights_size);
            for (int16_t i = 0; i < fights_size; ++i)
                fights[i] = std::make_unique<fight_external_informations>(data);
        }
    };
}

#endif
