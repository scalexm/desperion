//  Generated by desperion protocol_builder

#ifndef core_notification_by_server_message_hpp
#define core_notification_by_server_message_hpp

namespace network
{
    struct notification_by_server_message : dofus_unit
    {
        int16_t id;
        std::vector<std::string> parameters;
        bool force_open;
        
        int16_t id() const override
        { return 6103; } 
        
        notification_by_server_message(const int16_t & id, const std::vector<std::string> & parameters, const bool & force_open)
        {
            _data << id;
            _data << static_cast<int16_t>(parameters.size());
            for (auto && i : parameters)
                _data << i;
            _data << force_open;
        }
        
        notification_by_server_message(byte_buffer & data)
        {
            data >> id;
            int16_t parameters_size;
            data >> parameters_size;
            parameters.resize(parameters_size);
            for (int16_t i = 0; i < parameters_size; ++i)
                data >> parameters[i];
            data >> force_open;
        }
    };
}

#endif