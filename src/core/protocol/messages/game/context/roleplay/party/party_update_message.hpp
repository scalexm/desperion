//  Generated by desperion protocol_builder

#ifndef core_party_update_message_hpp
#define core_party_update_message_hpp

namespace protocol
{
    struct party_update_message : abstract_party_event_message
    {
        party_member_informations_ptr member_informations;
        
        int16_t id() const override
        { return 5575; } 
        
        party_update_message(const int32_t & party_id, const party_member_informations_ptr & member_informations) : abstract_party_event_message { party_id }
        {
            _data << member_informations->id() << member_informations->buffer();
        }
        
        party_update_message(byte_buffer & data) : abstract_party_event_message { data }
        {
            int16_t member_informations_id;
            data >> member_informations_id;
            member_informations.reset(type_manager::get_party_member_informations(member_informations_id, data));
        }
    };
}

#endif
