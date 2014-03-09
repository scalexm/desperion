//  Generated by desperion protocol_builder

#ifndef core_notification_list_message_hpp
#define core_notification_list_message_hpp

namespace protocol
{
    struct notification_list_message : dofus_unit
    {
        std::vector<int32_t> flags;
        
        int16_t id() const override
        { return 6087; } 
        
        notification_list_message(const std::vector<int32_t> & flags)
        {
            _data << static_cast<int16_t>(flags.size());
            for (auto && i : flags)
                _data << i;
        }
        
        notification_list_message(byte_buffer & data)
        {
            int16_t flags_size;
            data >> flags_size;
            flags.resize(flags_size);
            for (int16_t i = 0; i < flags_size; ++i)
                data >> flags[i];
        }
    };
}

#endif
