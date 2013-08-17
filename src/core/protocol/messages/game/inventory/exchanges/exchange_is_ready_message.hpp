//  Generated by desperion protocol_builder

#ifndef core_exchange_is_ready_message_hpp
#define core_exchange_is_ready_message_hpp

namespace network
{
    struct exchange_is_ready_message : dofus_unit
    {
        int32_t id;
        bool ready;
        
        int16_t id() const override
        { return 5509; } 
        
        exchange_is_ready_message(const int32_t & id, const bool & ready)
        {
            _data << id;
            _data << ready;
        }
        
        exchange_is_ready_message(byte_buffer & data)
        {
            data >> id;
            data >> ready;
        }
    };
}

#endif
