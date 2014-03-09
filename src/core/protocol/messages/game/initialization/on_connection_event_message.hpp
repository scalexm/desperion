//  Generated by desperion protocol_builder

#ifndef core_on_connection_event_message_hpp
#define core_on_connection_event_message_hpp

namespace protocol
{
    struct on_connection_event_message : dofus_unit
    {
        int8_t event_type;
        
        int16_t id() const override
        { return 5726; } 
        
        on_connection_event_message(const int8_t & event_type)
        {
            _data << event_type;
        }
        
        on_connection_event_message(byte_buffer & data)
        {
            data >> event_type;
        }
    };
}

#endif
