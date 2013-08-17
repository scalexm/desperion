//  Generated by desperion protocol_builder

#ifndef core_current_map_message_hpp
#define core_current_map_message_hpp

namespace network
{
    struct current_map_message : dofus_unit
    {
        int32_t map_id;
        std::string map_key;
        
        int16_t id() const override
        { return 220; } 
        
        current_map_message(const int32_t & map_id, const std::string & map_key)
        {
            _data << map_id;
            _data << map_key;
        }
        
        current_map_message(byte_buffer & data)
        {
            data >> map_id;
            data >> map_key;
        }
    };
}

#endif
