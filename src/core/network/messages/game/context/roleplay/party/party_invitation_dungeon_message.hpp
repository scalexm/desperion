//  Generated by desperion protocol_builder

#ifndef core_party_invitation_dungeon_message_hpp
#define core_party_invitation_dungeon_message_hpp

namespace network
{
    struct party_invitation_dungeon_message : party_invitation_message
    {
        int16_t dungeon_id;
        
        int16_t id() const override
        { return 6244; } 
        
        party_invitation_dungeon_message(const int8_t & party_type, const int8_t & max_participants, const int32_t & from_id, const std::string & from_name, const int32_t & to_id, const int32_t & party_id, const int16_t & dungeon_id) : party_invitation_message { party_type,max_participants,from_id,from_name,to_id,party_id }
        {
            _data << dungeon_id;
        }
        
        party_invitation_dungeon_message(byte_buffer & data) : party_invitation_message { data }
        {
            data >> dungeon_id;
        }
    };
}

#endif
