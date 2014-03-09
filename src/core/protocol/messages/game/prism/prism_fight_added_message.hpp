//  Generated by desperion protocol_builder

#ifndef core_prism_fight_added_message_hpp
#define core_prism_fight_added_message_hpp

namespace protocol
{
    struct prism_fight_added_message : dofus_unit
    {
        prism_fighters_information_ptr fight;
        
        int16_t id() const override
        { return 6452; } 
        
        prism_fight_added_message(const prism_fighters_information_ptr & fight)
        {
            _data << fight->buffer();
        }
        
        prism_fight_added_message(byte_buffer & data)
        {
            fight = std::make_unique<prism_fighters_information>(data);
        }
    };
}

#endif
