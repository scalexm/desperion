//  Generated by desperion protocol_builder

#ifndef core_character_name_suggestion_request_message_hpp
#define core_character_name_suggestion_request_message_hpp

namespace protocol
{
    struct character_name_suggestion_request_message : dofus_unit
    {
        
        int16_t id() const override
        { return 162; } 
        
        character_name_suggestion_request_message()
        {
        }
        
        character_name_suggestion_request_message(byte_buffer & data)
        {
        }
    };
}

#endif
