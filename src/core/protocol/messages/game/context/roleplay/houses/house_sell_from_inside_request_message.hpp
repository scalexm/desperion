//  Generated by desperion protocol_builder

#ifndef core_house_sell_from_inside_request_message_hpp
#define core_house_sell_from_inside_request_message_hpp

namespace protocol
{
    struct house_sell_from_inside_request_message : house_sell_request_message
    {
        
        int16_t id() const override
        { return 5884; } 
        
        house_sell_from_inside_request_message(const int32_t & amount) : house_sell_request_message { amount }
        {
        }
        
        house_sell_from_inside_request_message(byte_buffer & data) : house_sell_request_message { data }
        {
        }
    };
}

#endif
