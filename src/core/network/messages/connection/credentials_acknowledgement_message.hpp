//  Generated by desperion protocol_builder

#ifndef core_credentials_acknowledgement_message_hpp
#define core_credentials_acknowledgement_message_hpp

namespace network
{
    struct credentials_acknowledgement_message : dofus_unit
    {
        
        int16_t id() const override
        { return 6314; } 
        
        credentials_acknowledgement_message()
        {
        }
        
        credentials_acknowledgement_message(byte_buffer & data)
        {
        }
    };
}

#endif