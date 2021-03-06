//  Generated by desperion protocol_builder

#ifndef core_house_to_sell_list_request_message_hpp
#define core_house_to_sell_list_request_message_hpp

namespace protocol
{
    struct house_to_sell_list_request_message : dofus_unit
    {
        int16_t page_index;
        
        int16_t id() const override
        { return 6139; } 
        
        house_to_sell_list_request_message(const int16_t & page_index)
        {
            _data << page_index;
        }
        
        house_to_sell_list_request_message(byte_buffer & data)
        {
            data >> page_index;
        }
    };
}

#endif
