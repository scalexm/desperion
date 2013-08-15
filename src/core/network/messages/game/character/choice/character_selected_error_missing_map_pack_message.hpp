//  Generated by desperion protocol_builder

#ifndef core_character_selected_error_missing_map_pack_message_hpp
#define core_character_selected_error_missing_map_pack_message_hpp

namespace network
{
    struct character_selected_error_missing_map_pack_message : character_selected_error_message
    {
        int32_t sub_area_id;
        
        int16_t id() const override
        { return 6300; } 
        
        character_selected_error_missing_map_pack_message(const int32_t & sub_area_id)
        {
            _data << sub_area_id;
        }
        
        character_selected_error_missing_map_pack_message(byte_buffer & data) : character_selected_error_message { data }
        {
            data >> sub_area_id;
        }
    };
}

#endif
