//  Generated by desperion protocol_builder

#ifndef core_game_fight_placement_possible_positions_message_hpp
#define core_game_fight_placement_possible_positions_message_hpp

namespace protocol
{
    struct game_fight_placement_possible_positions_message : dofus_unit
    {
        std::vector<int16_t> positions_for_challengers;
        std::vector<int16_t> positions_for_defenders;
        int8_t team_number;
        
        int16_t id() const override
        { return 703; } 
        
        game_fight_placement_possible_positions_message(const std::vector<int16_t> & positions_for_challengers, const std::vector<int16_t> & positions_for_defenders, const int8_t & team_number)
        {
            _data << static_cast<int16_t>(positions_for_challengers.size());
            for (auto && i : positions_for_challengers)
                _data << i;
            _data << static_cast<int16_t>(positions_for_defenders.size());
            for (auto && i : positions_for_defenders)
                _data << i;
            _data << team_number;
        }
        
        game_fight_placement_possible_positions_message(byte_buffer & data)
        {
            int16_t positions_for_challengers_size;
            data >> positions_for_challengers_size;
            positions_for_challengers.resize(positions_for_challengers_size);
            for (int16_t i = 0; i < positions_for_challengers_size; ++i)
                data >> positions_for_challengers[i];
            int16_t positions_for_defenders_size;
            data >> positions_for_defenders_size;
            positions_for_defenders.resize(positions_for_defenders_size);
            for (int16_t i = 0; i < positions_for_defenders_size; ++i)
                data >> positions_for_defenders[i];
            data >> team_number;
        }
    };
}

#endif
