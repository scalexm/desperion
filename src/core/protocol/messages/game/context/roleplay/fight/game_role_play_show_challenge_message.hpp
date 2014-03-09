//  Generated by desperion protocol_builder

#ifndef core_game_role_play_show_challenge_message_hpp
#define core_game_role_play_show_challenge_message_hpp

namespace protocol
{
    struct game_role_play_show_challenge_message : dofus_unit
    {
        fight_common_informations_ptr commons_infos;
        
        int16_t id() const override
        { return 301; } 
        
        game_role_play_show_challenge_message(const fight_common_informations_ptr & commons_infos)
        {
            _data << commons_infos->buffer();
        }
        
        game_role_play_show_challenge_message(byte_buffer & data)
        {
            commons_infos = std::make_unique<fight_common_informations>(data);
        }
    };
}

#endif
