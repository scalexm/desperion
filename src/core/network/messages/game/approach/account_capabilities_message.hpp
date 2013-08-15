//  Generated by desperion protocol_builder

#ifndef core_account_capabilities_message_hpp
#define core_account_capabilities_message_hpp

namespace network
{
    struct account_capabilities_message : dofus_unit
    {
        int32_t account_id;
        bool tutorial_available;
        int16_t breeds_visible;
        int16_t breeds_available;
        int8_t status;
        
        int16_t id() const override
        { return 6216; } 
        
        account_capabilities_message(const int32_t & account_id, const bool & tutorial_available, const int16_t & breeds_visible, const int16_t & breeds_available, const int8_t & status)
        {
            _data << account_id;
            _data << tutorial_available;
            _data << breeds_visible;
            _data << breeds_available;
            _data << status;
        }
        
        account_capabilities_message(byte_buffer & data)
        {
            data >> account_id;
            data >> tutorial_available;
            data >> breeds_visible;
            data >> breeds_available;
            data >> status;
        }
    };
}

#endif
