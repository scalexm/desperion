//  Generated by desperion protocol_builder

#ifndef core_house_kick_request_message_hpp
#define core_house_kick_request_message_hpp

namespace network
{
    struct house_kick_request_message : dofus_unit
    {
        int32_t id;
        
        int16_t id() const override
        { return 5698; } 
        
        house_kick_request_message(const int32_t & id)
        {
            _data << id;
        }
        
        house_kick_request_message(byte_buffer & data)
        {
            data >> id;
        }
    };
}

#endif