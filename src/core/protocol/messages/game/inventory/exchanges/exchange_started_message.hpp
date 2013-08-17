//  Generated by desperion protocol_builder

#ifndef core_exchange_started_message_hpp
#define core_exchange_started_message_hpp

namespace network
{
    struct exchange_started_message : dofus_unit
    {
        int8_t exchange_type;
        
        int16_t id() const override
        { return 5512; } 
        
        exchange_started_message(const int8_t & exchange_type)
        {
            _data << exchange_type;
        }
        
        exchange_started_message(byte_buffer & data)
        {
            data >> exchange_type;
        }
    };
}

#endif
