//  Generated by desperion protocol_builder

#ifndef core_character_selection_with_recolor_message_hpp
#define core_character_selection_with_recolor_message_hpp

namespace protocol
{
    struct character_selection_with_recolor_message : character_selection_message
    {
        std::vector<int32_t> indexed_color;
        
        int16_t id() const override
        { return 6075; } 
        
        character_selection_with_recolor_message(const int32_t & id, const std::vector<int32_t> & indexed_color) : character_selection_message { id }
        {
            _data << static_cast<int16_t>(indexed_color.size());
            for (auto && i : indexed_color)
                _data << i;
        }
        
        character_selection_with_recolor_message(byte_buffer & data) : character_selection_message { data }
        {
            int16_t indexed_color_size;
            data >> indexed_color_size;
            indexed_color.resize(indexed_color_size);
            for (int16_t i = 0; i < indexed_color_size; ++i)
                data >> indexed_color[i];
        }
    };
}

#endif
