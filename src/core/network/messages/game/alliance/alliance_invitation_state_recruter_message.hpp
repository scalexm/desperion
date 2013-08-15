//  Generated by desperion protocol_builder

#ifndef core_alliance_invitation_state_recruter_message_hpp
#define core_alliance_invitation_state_recruter_message_hpp

namespace network
{
    struct alliance_invitation_state_recruter_message : dofus_unit
    {
        std::string recruted_name;
        int8_t invitation_state;
        
        int16_t id() const override
        { return 6396; } 
        
        alliance_invitation_state_recruter_message(const std::string & recruted_name, const int8_t & invitation_state)
        {
            _data << recruted_name;
            _data << invitation_state;
        }
        
        alliance_invitation_state_recruter_message(byte_buffer & data)
        {
            data >> recruted_name;
            data >> invitation_state;
        }
    };
}

#endif
