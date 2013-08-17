//  Generated by desperion protocol_builder

#ifndef core_dungeon_party_finder_player_hpp
#define core_dungeon_party_finder_player_hpp

namespace network
{
    struct dungeon_party_finder_player : dofus_unit
    {
        int32_t player_id;
        std::string player_name;
        int8_t breed;
        bool sex;
        int16_t level;
        
        int16_t id() const override
        { return 373; } 
        
        dungeon_party_finder_player(const int32_t & player_id, const std::string & player_name, const int8_t & breed, const bool & sex, const int16_t & level)
        {
            _data << player_id;
            _data << player_name;
            _data << breed;
            _data << sex;
            _data << level;
        }
        
        dungeon_party_finder_player(byte_buffer & data)
        {
            data >> player_id;
            data >> player_name;
            data >> breed;
            data >> sex;
            data >> level;
        }
    };
    
    using dungeon_party_finder_player_ptr = std::unique_ptr<dungeon_party_finder_player>;
}

#endif