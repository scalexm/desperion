//  Generated by desperion protocol_builder

#ifndef core_chat_message_report_message_hpp
#define core_chat_message_report_message_hpp

namespace protocol
{
    struct chat_message_report_message : dofus_unit
    {
        std::string sender_name;
        std::string content;
        int32_t timestamp;
        int8_t channel;
        std::string fingerprint;
        int8_t reason;
        
        int16_t id() const override
        { return 821; } 
        
        chat_message_report_message(const std::string & sender_name, const std::string & content, const int32_t & timestamp, const int8_t & channel, const std::string & fingerprint, const int8_t & reason)
        {
            _data << sender_name;
            _data << content;
            _data << timestamp;
            _data << channel;
            _data << fingerprint;
            _data << reason;
        }
        
        chat_message_report_message(byte_buffer & data)
        {
            data >> sender_name;
            data >> content;
            data >> timestamp;
            data >> channel;
            data >> fingerprint;
            data >> reason;
        }
    };
}

#endif
