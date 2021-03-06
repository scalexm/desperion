//  Generated by desperion protocol_builder

#ifndef core_house_buy_request_message_hpp
#define core_house_buy_request_message_hpp

namespace protocol
{
    struct house_buy_request_message : dofus_unit
    {
        int32_t proposed_price;
        
        int16_t id() const override
        { return 5738; } 
        
        house_buy_request_message(const int32_t & proposed_price)
        {
            _data << proposed_price;
        }
        
        house_buy_request_message(byte_buffer & data)
        {
            data >> proposed_price;
        }
    };
}

#endif
