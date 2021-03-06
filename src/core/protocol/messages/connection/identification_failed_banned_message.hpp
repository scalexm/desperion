//  Generated by desperion protocol_builder

#ifndef core_identification_failed_banned_message_hpp
#define core_identification_failed_banned_message_hpp

namespace protocol
{
    struct identification_failed_banned_message : identification_failed_message
    {
        double ban_end_date;
        
        int16_t id() const override
        { return 6174; } 
        
        identification_failed_banned_message(const int8_t & reason, const double & ban_end_date) : identification_failed_message { reason }
        {
            _data << ban_end_date;
        }
        
        identification_failed_banned_message(byte_buffer & data) : identification_failed_message { data }
        {
            data >> ban_end_date;
        }
    };
}

#endif
