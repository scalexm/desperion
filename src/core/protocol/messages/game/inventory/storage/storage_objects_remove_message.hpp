//  Generated by desperion protocol_builder

#ifndef core_storage_objects_remove_message_hpp
#define core_storage_objects_remove_message_hpp

namespace protocol
{
    struct storage_objects_remove_message : dofus_unit
    {
        std::vector<int32_t> object_u_i_d_list;
        
        int16_t id() const override
        { return 6035; } 
        
        storage_objects_remove_message(const std::vector<int32_t> & object_u_i_d_list)
        {
            _data << static_cast<int16_t>(object_u_i_d_list.size());
            for (auto && i : object_u_i_d_list)
                _data << i;
        }
        
        storage_objects_remove_message(byte_buffer & data)
        {
            int16_t object_u_i_d_list_size;
            data >> object_u_i_d_list_size;
            object_u_i_d_list.resize(object_u_i_d_list_size);
            for (int16_t i = 0; i < object_u_i_d_list_size; ++i)
                data >> object_u_i_d_list[i];
        }
    };
}

#endif
