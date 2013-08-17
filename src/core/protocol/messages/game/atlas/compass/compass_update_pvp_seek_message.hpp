//  Generated by desperion protocol_builder

#ifndef core_compass_update_pvp_seek_message_hpp
#define core_compass_update_pvp_seek_message_hpp

namespace network
{
    struct compass_update_pvp_seek_message : compass_update_message
    {
        int32_t member_id;
        std::string member_name;
        
        int16_t id() const override
        { return 6013; } 
        
        compass_update_pvp_seek_message(const int8_t & type, const int16_t & world_x, const int16_t & world_y, const int32_t & member_id, const std::string & member_name) : compass_update_message { type,world_x,world_y }
        {
            _data << member_id;
            _data << member_name;
        }
        
        compass_update_pvp_seek_message(byte_buffer & data) : compass_update_message { data }
        {
            data >> member_id;
            data >> member_name;
        }
    };
}

#endif
