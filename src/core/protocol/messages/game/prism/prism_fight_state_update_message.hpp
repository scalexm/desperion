//  Generated by desperion protocol_builder

#ifndef core_prism_fight_state_update_message_hpp
#define core_prism_fight_state_update_message_hpp

namespace network
{
    struct prism_fight_state_update_message : dofus_unit
    {
        int8_t state;
        
        int16_t id() const override
        { return 6040; } 
        
        prism_fight_state_update_message(const int8_t & state)
        {
            _data << state;
        }
        
        prism_fight_state_update_message(byte_buffer & data)
        {
            data >> state;
        }
    };
}

#endif
