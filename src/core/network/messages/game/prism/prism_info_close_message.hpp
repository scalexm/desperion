//  Generated by desperion protocol_builder

#ifndef core_prism_info_close_message_hpp
#define core_prism_info_close_message_hpp

namespace network
{
    struct prism_info_close_message : dofus_unit
    {
        
        int16_t id() const override
        { return 5853; } 
        
        prism_info_close_message()
        {
        }
        
        prism_info_close_message(byte_buffer & data)
        {
        }
    };
}

#endif