//  Generated by desperion protocol_builder

#ifndef core_spell_upgrade_success_message_hpp
#define core_spell_upgrade_success_message_hpp

namespace network
{
    struct spell_upgrade_success_message : dofus_unit
    {
        int32_t spell_id;
        int8_t spell_level;
        
        int16_t id() const override
        { return 1201; } 
        
        spell_upgrade_success_message(const int32_t & spell_id, const int8_t & spell_level)
        {
            _data << spell_id;
            _data << spell_level;
        }
        
        spell_upgrade_success_message(byte_buffer & data)
        {
            data >> spell_id;
            data >> spell_level;
        }
    };
}

#endif
