//  Generated by desperion protocol_builder

#ifndef core_koh_update_message_hpp
#define core_koh_update_message_hpp

namespace network
{
    struct koh_update_message : dofus_unit
    {
        std::vector<alliance_informations_ptr> alliances;
        std::vector<int16_t> alliance_nb_members;
        std::vector<int32_t> alliance_round_weigth;
        std::vector<int8_t> alliance_match_score;
        
        int16_t id() const override
        { return 6439; } 
        
        koh_update_message(const std::vector<alliance_informations_ptr> & alliances, const std::vector<int16_t> & alliance_nb_members, const std::vector<int32_t> & alliance_round_weigth, const std::vector<int8_t> & alliance_match_score)
        {
            _data << static_cast<int16_t>(alliances.size());
            for (auto && i : alliances)
                _data << i->buffer();
            _data << static_cast<int16_t>(alliance_nb_members.size());
            for (auto && i : alliance_nb_members)
                _data << i;
            _data << static_cast<int16_t>(alliance_round_weigth.size());
            for (auto && i : alliance_round_weigth)
                _data << i;
            _data << alliance_match_score;
        }
        
        koh_update_message(byte_buffer & data)
        {
            int16_t alliances_size;
            data >> alliances_size;
            alliances.resize(alliances_size);
            for (int16_t i = 0; i < alliances_size; ++i)
                alliances[i] = std::make_unique<alliance_informations>(data);
            int16_t alliance_nb_members_size;
            data >> alliance_nb_members_size;
            alliance_nb_members.resize(alliance_nb_members_size);
            for (int16_t i = 0; i < alliance_nb_members_size; ++i)
                data >> alliance_nb_members[i];
            int16_t alliance_round_weigth_size;
            data >> alliance_round_weigth_size;
            alliance_round_weigth.resize(alliance_round_weigth_size);
            for (int16_t i = 0; i < alliance_round_weigth_size; ++i)
                data >> alliance_round_weigth[i];
            data >> alliance_match_score;
        }
    };
}

#endif