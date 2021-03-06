//  Generated by desperion protocol_builder

#ifndef core_contact_look_request_message_hpp
#define core_contact_look_request_message_hpp

namespace protocol
{
    struct contact_look_request_message : dofus_unit
    {
        int8_t request_id;
        int8_t contact_type;
        
        int16_t id() const override
        { return 5932; } 
        
        contact_look_request_message(const int8_t & request_id, const int8_t & contact_type)
        {
            _data << request_id;
            _data << contact_type;
        }
        
        contact_look_request_message(byte_buffer & data)
        {
            data >> request_id;
            data >> contact_type;
        }
    };
}

#endif
