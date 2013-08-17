//  Generated by desperion protocol_builder

#ifndef core_server_settings_message_hpp
#define core_server_settings_message_hpp

namespace network
{
    struct server_settings_message : dofus_unit
    {
        std::string lang;
        int8_t community;
        int8_t game_type;
        
        int16_t id() const override
        { return 6340; } 
        
        server_settings_message(const std::string & lang, const int8_t & community, const int8_t & game_type)
        {
            _data << lang;
            _data << community;
            _data << game_type;
        }
        
        server_settings_message(byte_buffer & data)
        {
            data >> lang;
            data >> community;
            data >> game_type;
        }
    };
}

#endif