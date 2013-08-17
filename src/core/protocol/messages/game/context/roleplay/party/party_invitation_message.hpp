//  Generated by desperion protocol_builder

#ifndef core_party_invitation_message_hpp
#define core_party_invitation_message_hpp

namespace network
{
    struct party_invitation_message : abstract_party_message
    {
        int8_t party_type;
        int8_t max_participants;
        int32_t from_id;
        std::string from_name;
        int32_t to_id;
        
        int16_t id() const override
        { return 5586; } 
        
        party_invitation_message(const int32_t & party_id, const int8_t & party_type, const int8_t & max_participants, const int32_t & from_id, const std::string & from_name, const int32_t & to_id) : abstract_party_message { party_id }
        {
            _data << party_type;
            _data << max_participants;
            _data << from_id;
            _data << from_name;
            _data << to_id;
        }
        
        party_invitation_message(byte_buffer & data) : abstract_party_message { data }
        {
            data >> party_type;
            data >> max_participants;
            data >> from_id;
            data >> from_name;
            data >> to_id;
        }
    };
}

#endif
