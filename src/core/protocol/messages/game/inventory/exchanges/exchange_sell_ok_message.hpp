//  Generated by desperion protocol_builder

#ifndef core_exchange_sell_ok_message_hpp
#define core_exchange_sell_ok_message_hpp

namespace protocol
{
    struct exchange_sell_ok_message : dofus_unit
    {
        
        int16_t id() const override
        { return 5792; } 
        
        exchange_sell_ok_message()
        {
        }
        
        exchange_sell_ok_message(byte_buffer & data)
        {
        }
    };
}

#endif
