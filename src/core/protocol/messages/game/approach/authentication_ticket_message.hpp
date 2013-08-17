//  Generated by desperion protocol_builder

#ifndef core_authentication_ticket_message_hpp
#define core_authentication_ticket_message_hpp

namespace network
{
    struct authentication_ticket_message : dofus_unit
    {
        std::string lang;
        std::string ticket;
        
        int16_t id() const override
        { return 110; } 
        
        authentication_ticket_message(const std::string & lang, const std::string & ticket)
        {
            _data << lang;
            _data << ticket;
        }
        
        authentication_ticket_message(byte_buffer & data)
        {
            data >> lang;
            data >> ticket;
        }
    };
}

#endif
