//  Generated by desperion protocol_builder

#ifndef core_character_creation_result_message_hpp
#define core_character_creation_result_message_hpp

namespace protocol
{
    struct character_creation_result_message : dofus_unit
    {
        int8_t result;
        
        int16_t id() const override
        { return 161; } 
        
        character_creation_result_message(const int8_t & result)
        {
            _data << result;
        }
        
        character_creation_result_message(byte_buffer & data)
        {
            data >> result;
        }
    };
}

#endif
