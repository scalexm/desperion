//  Generated by desperion protocol_builder

#ifndef core_characters_list_request_message_hpp
#define core_characters_list_request_message_hpp

namespace protocol
{
    struct characters_list_request_message : dofus_unit
    {
        
        int16_t id() const override
        { return 150; } 
        
        characters_list_request_message()
        {
        }
        
        characters_list_request_message(byte_buffer & data)
        {
        }
    };
}

#endif
