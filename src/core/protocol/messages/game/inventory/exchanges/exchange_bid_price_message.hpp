//  Generated by desperion protocol_builder

#ifndef core_exchange_bid_price_message_hpp
#define core_exchange_bid_price_message_hpp

namespace protocol
{
    struct exchange_bid_price_message : dofus_unit
    {
        int32_t generic_id;
        int32_t average_price;
        
        int16_t id() const override
        { return 5755; } 
        
        exchange_bid_price_message(const int32_t & generic_id, const int32_t & average_price)
        {
            _data << generic_id;
            _data << average_price;
        }
        
        exchange_bid_price_message(byte_buffer & data)
        {
            data >> generic_id;
            data >> average_price;
        }
    };
}

#endif
