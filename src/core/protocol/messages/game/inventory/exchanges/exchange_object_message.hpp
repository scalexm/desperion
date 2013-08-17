//  Generated by desperion protocol_builder

#ifndef core_exchange_object_message_hpp
#define core_exchange_object_message_hpp

namespace network
{
    struct exchange_object_message : dofus_unit
    {
        bool remote;
        
        int16_t id() const override
        { return 5515; } 
        
        exchange_object_message(const bool & remote)
        {
            _data << remote;
        }
        
        exchange_object_message(byte_buffer & data)
        {
            data >> remote;
        }
    };
}

#endif
