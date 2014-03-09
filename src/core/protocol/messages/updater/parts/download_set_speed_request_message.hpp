//  Generated by desperion protocol_builder

#ifndef core_download_set_speed_request_message_hpp
#define core_download_set_speed_request_message_hpp

namespace protocol
{
    struct download_set_speed_request_message : dofus_unit
    {
        int8_t download_speed;
        
        int16_t id() const override
        { return 1512; } 
        
        download_set_speed_request_message(const int8_t & download_speed)
        {
            _data << download_speed;
        }
        
        download_set_speed_request_message(byte_buffer & data)
        {
            data >> download_speed;
        }
    };
}

#endif
