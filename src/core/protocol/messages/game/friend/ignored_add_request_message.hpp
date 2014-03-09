//  Generated by desperion protocol_builder

#ifndef core_ignored_add_request_message_hpp
#define core_ignored_add_request_message_hpp

namespace protocol
{
    struct ignored_add_request_message : dofus_unit
    {
        std::string name;
        bool session;
        
        int16_t id() const override
        { return 5673; } 
        
        ignored_add_request_message(const std::string & name, const bool & session)
        {
            _data << name;
            _data << session;
        }
        
        ignored_add_request_message(byte_buffer & data)
        {
            data >> name;
            data >> session;
        }
    };
}

#endif
