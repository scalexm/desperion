//  Generated by desperion protocol_builder

#ifndef core_paddock_to_sell_list_request_message_hpp
#define core_paddock_to_sell_list_request_message_hpp

namespace protocol
{
    struct paddock_to_sell_list_request_message : dofus_unit
    {
        int16_t page_index;
        
        int16_t id() const override
        { return 6141; } 
        
        paddock_to_sell_list_request_message(const int16_t & page_index)
        {
            _data << page_index;
        }
        
        paddock_to_sell_list_request_message(byte_buffer & data)
        {
            data >> page_index;
        }
    };
}

#endif
