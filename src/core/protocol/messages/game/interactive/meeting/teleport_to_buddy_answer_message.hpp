//  Generated by desperion protocol_builder

#ifndef core_teleport_to_buddy_answer_message_hpp
#define core_teleport_to_buddy_answer_message_hpp

namespace network
{
    struct teleport_to_buddy_answer_message : dofus_unit
    {
        int16_t dungeon_id;
        int32_t buddy_id;
        bool accept;
        
        int16_t id() const override
        { return 6293; } 
        
        teleport_to_buddy_answer_message(const int16_t & dungeon_id, const int32_t & buddy_id, const bool & accept)
        {
            _data << dungeon_id;
            _data << buddy_id;
            _data << accept;
        }
        
        teleport_to_buddy_answer_message(byte_buffer & data)
        {
            data >> dungeon_id;
            data >> buddy_id;
            data >> accept;
        }
    };
}

#endif
