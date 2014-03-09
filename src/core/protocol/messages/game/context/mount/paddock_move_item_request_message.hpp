//  Generated by desperion protocol_builder

#ifndef core_paddock_move_item_request_message_hpp
#define core_paddock_move_item_request_message_hpp

namespace protocol
{
    struct paddock_move_item_request_message : dofus_unit
    {
        int16_t old_cell_id;
        int16_t new_cell_id;
        
        int16_t id() const override
        { return 6052; } 
        
        paddock_move_item_request_message(const int16_t & old_cell_id, const int16_t & new_cell_id)
        {
            _data << old_cell_id;
            _data << new_cell_id;
        }
        
        paddock_move_item_request_message(byte_buffer & data)
        {
            data >> old_cell_id;
            data >> new_cell_id;
        }
    };
}

#endif
