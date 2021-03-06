//  Generated by desperion protocol_builder

#ifndef core_spell_list_message_hpp
#define core_spell_list_message_hpp

namespace protocol
{
    struct spell_list_message : dofus_unit
    {
        bool spell_previsualization;
        std::vector<spell_item_ptr> spells;
        
        int16_t id() const override
        { return 1200; } 
        
        spell_list_message(const bool & spell_previsualization, const std::vector<spell_item_ptr> & spells)
        {
            _data << spell_previsualization;
            _data << static_cast<int16_t>(spells.size());
            for (auto && i : spells)
                _data << i->buffer();
        }
        
        spell_list_message(byte_buffer & data)
        {
            data >> spell_previsualization;
            int16_t spells_size;
            data >> spells_size;
            spells.resize(spells_size);
            for (int16_t i = 0; i < spells_size; ++i)
                spells[i] = std::make_unique<spell_item>(data);
        }
    };
}

#endif
