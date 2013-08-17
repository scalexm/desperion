//  Generated by desperion protocol_builder

#ifndef core_teleport_buddies_answer_message_hpp
#define core_teleport_buddies_answer_message_hpp

namespace network
{
    struct teleport_buddies_answer_message : dofus_unit
    {
        bool accept;
        
        int16_t id() const override
        { return 6294; } 
        
        teleport_buddies_answer_message(const bool & accept)
        {
            _data << accept;
        }
        
        teleport_buddies_answer_message(byte_buffer & data)
        {
            data >> accept;
        }
    };
}

#endif
