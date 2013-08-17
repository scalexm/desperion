//  Generated by desperion protocol_builder

#ifndef core_objects_quantity_message_hpp
#define core_objects_quantity_message_hpp

namespace network
{
    struct objects_quantity_message : dofus_unit
    {
        std::vector<object_item_quantity_ptr> objects_u_i_d_and_qty;
        
        int16_t id() const override
        { return 6206; } 
        
        objects_quantity_message(const std::vector<object_item_quantity_ptr> & objects_u_i_d_and_qty)
        {
            _data << static_cast<int16_t>(objects_u_i_d_and_qty.size());
            for (auto && i : objects_u_i_d_and_qty)
                _data << i->buffer();
        }
        
        objects_quantity_message(byte_buffer & data)
        {
            int16_t objects_u_i_d_and_qty_size;
            data >> objects_u_i_d_and_qty_size;
            objects_u_i_d_and_qty.resize(objects_u_i_d_and_qty_size);
            for (int16_t i = 0; i < objects_u_i_d_and_qty_size; ++i)
                objects_u_i_d_and_qty[i] = std::make_unique<object_item_quantity>(data);
        }
    };
}

#endif