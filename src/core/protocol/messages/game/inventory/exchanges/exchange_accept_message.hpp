//  Generated by desperion protocol_builder

#ifndef core_exchange_accept_message_hpp
#define core_exchange_accept_message_hpp

namespace network
{
    struct exchange_accept_message : dofus_unit
    {
        
        int16_t id() const override
        { return 5508; } 
        
        exchange_accept_message()
        {
        }
        
        exchange_accept_message(byte_buffer & data)
        {
        }
    };
}

#endif