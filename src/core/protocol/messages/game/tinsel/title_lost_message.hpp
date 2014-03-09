//  Generated by desperion protocol_builder

#ifndef core_title_lost_message_hpp
#define core_title_lost_message_hpp

namespace protocol
{
    struct title_lost_message : dofus_unit
    {
        int16_t title_id;
        
        int16_t id() const override
        { return 6371; } 
        
        title_lost_message(const int16_t & title_id)
        {
            _data << title_id;
        }
        
        title_lost_message(byte_buffer & data)
        {
            data >> title_id;
        }
    };
}

#endif
