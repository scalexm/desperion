//  Generated by desperion protocol_builder

#ifndef core_paddock_sell_buy_dialog_message_hpp
#define core_paddock_sell_buy_dialog_message_hpp

namespace protocol
{
    struct paddock_sell_buy_dialog_message : dofus_unit
    {
        bool bsell;
        int32_t owner_id;
        int32_t price;
        
        int16_t id() const override
        { return 6018; } 
        
        paddock_sell_buy_dialog_message(const bool & bsell, const int32_t & owner_id, const int32_t & price)
        {
            _data << bsell;
            _data << owner_id;
            _data << price;
        }
        
        paddock_sell_buy_dialog_message(byte_buffer & data)
        {
            data >> bsell;
            data >> owner_id;
            data >> price;
        }
    };
}

#endif
