//  Generated by desperion protocol_builder

#ifndef core_exchange_reply_tax_vendor_message_hpp
#define core_exchange_reply_tax_vendor_message_hpp

namespace protocol
{
    struct exchange_reply_tax_vendor_message : dofus_unit
    {
        int32_t object_value;
        int32_t total_tax_value;
        
        int16_t id() const override
        { return 5787; } 
        
        exchange_reply_tax_vendor_message(const int32_t & object_value, const int32_t & total_tax_value)
        {
            _data << object_value;
            _data << total_tax_value;
        }
        
        exchange_reply_tax_vendor_message(byte_buffer & data)
        {
            data >> object_value;
            data >> total_tax_value;
        }
    };
}

#endif
