//  Generated by desperion protocol_builder

#ifndef core_exchange_request_on_tax_collector_message_hpp
#define core_exchange_request_on_tax_collector_message_hpp

namespace network
{
    struct exchange_request_on_tax_collector_message : dofus_unit
    {
        int32_t tax_collector_id;
        
        int16_t id() const override
        { return 5779; } 
        
        exchange_request_on_tax_collector_message(const int32_t & tax_collector_id)
        {
            _data << tax_collector_id;
        }
        
        exchange_request_on_tax_collector_message(byte_buffer & data)
        {
            data >> tax_collector_id;
        }
    };
}

#endif
