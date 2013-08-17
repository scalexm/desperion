//  Generated by desperion protocol_builder

#ifndef core_exchange_bid_house_buy_result_message_hpp
#define core_exchange_bid_house_buy_result_message_hpp

namespace network
{
    struct exchange_bid_house_buy_result_message : dofus_unit
    {
        int32_t uid;
        bool bought;
        
        int16_t id() const override
        { return 6272; } 
        
        exchange_bid_house_buy_result_message(const int32_t & uid, const bool & bought)
        {
            _data << uid;
            _data << bought;
        }
        
        exchange_bid_house_buy_result_message(byte_buffer & data)
        {
            data >> uid;
            data >> bought;
        }
    };
}

#endif