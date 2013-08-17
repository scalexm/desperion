//  Generated by desperion protocol_builder

#ifndef core_dungeon_party_finder_room_content_message_hpp
#define core_dungeon_party_finder_room_content_message_hpp

namespace network
{
    struct dungeon_party_finder_room_content_message : dofus_unit
    {
        int16_t dungeon_id;
        std::vector<dungeon_party_finder_player_ptr> players;
        
        int16_t id() const override
        { return 6247; } 
        
        dungeon_party_finder_room_content_message(const int16_t & dungeon_id, const std::vector<dungeon_party_finder_player_ptr> & players)
        {
            _data << dungeon_id;
            _data << static_cast<int16_t>(players.size());
            for (auto && i : players)
                _data << i->buffer();
        }
        
        dungeon_party_finder_room_content_message(byte_buffer & data)
        {
            data >> dungeon_id;
            int16_t players_size;
            data >> players_size;
            players.resize(players_size);
            for (int16_t i = 0; i < players_size; ++i)
                players[i] = std::make_unique<dungeon_party_finder_player>(data);
        }
    };
}

#endif