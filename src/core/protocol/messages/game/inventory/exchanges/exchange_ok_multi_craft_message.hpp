//  Generated by desperion protocol_builder

#ifndef core_exchange_ok_multi_craft_message_hpp
#define core_exchange_ok_multi_craft_message_hpp

namespace network
{
    struct exchange_ok_multi_craft_message : dofus_unit
    {
        int32_t initiator_id;
        int32_t other_id;
        int8_t role;
        
        int16_t id() const override
        { return 5768; } 
        
        exchange_ok_multi_craft_message(const int32_t & initiator_id, const int32_t & other_id, const int8_t & role)
        {
            _data << initiator_id;
            _data << other_id;
            _data << role;
        }
        
        exchange_ok_multi_craft_message(byte_buffer & data)
        {
            data >> initiator_id;
            data >> other_id;
            data >> role;
        }
    };
}

#endif