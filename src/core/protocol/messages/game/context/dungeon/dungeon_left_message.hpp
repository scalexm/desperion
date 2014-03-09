//  Generated by desperion protocol_builder

#ifndef core_dungeon_left_message_hpp
#define core_dungeon_left_message_hpp

namespace protocol
{
    struct dungeon_left_message : dofus_unit
    {
        int32_t dungeon_id;
        
        int16_t id() const override
        { return 6149; } 
        
        dungeon_left_message(const int32_t & dungeon_id)
        {
            _data << dungeon_id;
        }
        
        dungeon_left_message(byte_buffer & data)
        {
            data >> dungeon_id;
        }
    };
}

#endif
