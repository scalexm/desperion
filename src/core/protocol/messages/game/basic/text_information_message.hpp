//  Generated by desperion protocol_builder

#ifndef core_text_information_message_hpp
#define core_text_information_message_hpp

namespace protocol
{
    struct text_information_message : dofus_unit
    {
        int8_t msg_type;
        int16_t msg_id;
        std::vector<std::string> parameters;
        
        int16_t id() const override
        { return 780; } 
        
        text_information_message(const int8_t & msg_type, const int16_t & msg_id, const std::vector<std::string> & parameters)
        {
            _data << msg_type;
            _data << msg_id;
            _data << static_cast<int16_t>(parameters.size());
            for (auto && i : parameters)
                _data << i;
        }
        
        text_information_message(byte_buffer & data)
        {
            data >> msg_type;
            data >> msg_id;
            int16_t parameters_size;
            data >> parameters_size;
            parameters.resize(parameters_size);
            for (int16_t i = 0; i < parameters_size; ++i)
                data >> parameters[i];
        }
    };
}

#endif
