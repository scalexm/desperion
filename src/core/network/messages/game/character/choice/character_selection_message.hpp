//  Generated by desperion protocol_builder

#ifndef core_character_selection_message_hpp
#define core_character_selection_message_hpp

namespace network
{
    struct character_selection_message : dofus_unit
    {
        int32_t id;
        
        int16_t id() const override
        { return 152; } 
        
        character_selection_message(const int32_t & id)
        {
            _data << id;
        }
        
        character_selection_message(byte_buffer & data)
        {
            data >> id;
        }
    };
}

#endif
