//  Generated by desperion protocol_builder

#ifndef core_exchange_player_request_message_hpp
#define core_exchange_player_request_message_hpp

namespace network
{
    struct exchange_player_request_message : exchange_request_message
    {
        int32_t target;
        
        int16_t id() const override
        { return 5773; } 
        
        exchange_player_request_message(const int8_t & exchange_type, const int32_t & target) : exchange_request_message { exchange_type }
        {
            _data << target;
        }
        
        exchange_player_request_message(byte_buffer & data) : exchange_request_message { data }
        {
            data >> target;
        }
    };
}

#endif