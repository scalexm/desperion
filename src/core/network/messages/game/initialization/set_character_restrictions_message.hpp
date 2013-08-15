//  Generated by desperion protocol_builder

#ifndef core_set_character_restrictions_message_hpp
#define core_set_character_restrictions_message_hpp

namespace network
{
    struct set_character_restrictions_message : dofus_unit
    {
        actor_restrictions_informations_ptr restrictions;
        
        int16_t id() const override
        { return 170; } 
        
        set_character_restrictions_message(const actor_restrictions_informations_ptr & restrictions)
        {
            _data << restrictions->buffer();
        }
        
        set_character_restrictions_message(byte_buffer & data)
        {
            restrictions = std::make_unique<actor_restrictions_informations>(data);
        }
    };
}

#endif
