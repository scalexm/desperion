//  Generated by desperion protocol_builder

#ifndef core_game_data_paddock_object_remove_message_hpp
#define core_game_data_paddock_object_remove_message_hpp

namespace protocol
{
    struct game_data_paddock_object_remove_message : dofus_unit
    {
        int16_t cell_id;
        
        int16_t id() const override
        { return 5993; } 
        
        game_data_paddock_object_remove_message(const int16_t & cell_id)
        {
            _data << cell_id;
        }
        
        game_data_paddock_object_remove_message(byte_buffer & data)
        {
            data >> cell_id;
        }
    };
}

#endif
