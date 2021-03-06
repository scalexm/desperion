//  Generated by desperion protocol_builder

#ifndef core_object_use_on_cell_message_hpp
#define core_object_use_on_cell_message_hpp

namespace protocol
{
    struct object_use_on_cell_message : object_use_message
    {
        int16_t cells;
        
        int16_t id() const override
        { return 3013; } 
        
        object_use_on_cell_message(const int32_t & object_u_i_d, const int16_t & cells) : object_use_message { object_u_i_d }
        {
            _data << cells;
        }
        
        object_use_on_cell_message(byte_buffer & data) : object_use_message { data }
        {
            data >> cells;
        }
    };
}

#endif
