//  Generated by desperion protocol_builder

#ifndef core_party_new_member_message_hpp
#define core_party_new_member_message_hpp

namespace protocol
{
    struct party_new_member_message : party_update_message
    {
        
        int16_t id() const override
        { return 6306; } 
        
        party_new_member_message(const party_member_informations_ptr & member_informations, const int32_t & party_id) : party_update_message { member_informations,party_id }
        {
        }
        
        party_new_member_message(byte_buffer & data) : party_update_message { data }
        {
        }
    };
}

#endif
