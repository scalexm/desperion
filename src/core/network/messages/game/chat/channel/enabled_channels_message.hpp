//  Generated by desperion protocol_builder

#ifndef core_enabled_channels_message_hpp
#define core_enabled_channels_message_hpp

namespace network
{
    struct enabled_channels_message : dofus_unit
    {
        std::vector<int8_t> channels;
        std::vector<int8_t> disallowed;
        
        int16_t id() const override
        { return 892; } 
        
        enabled_channels_message(const std::vector<int8_t> & channels, const std::vector<int8_t> & disallowed)
        {
            _data << channels;
            _data << disallowed;
        }
        
        enabled_channels_message(byte_buffer & data)
        {
            data >> channels;
            data >> disallowed;
        }
    };
}

#endif
