//  Generated by desperion protocol_builder

#ifndef core_error_map_not_found_message_hpp
#define core_error_map_not_found_message_hpp

namespace protocol
{
    struct error_map_not_found_message : dofus_unit
    {
        int32_t map_id;
        
        int16_t id() const override
        { return 6197; } 
        
        error_map_not_found_message(const int32_t & map_id)
        {
            _data << map_id;
        }
        
        error_map_not_found_message(byte_buffer & data)
        {
            data >> map_id;
        }
    };
}

#endif
