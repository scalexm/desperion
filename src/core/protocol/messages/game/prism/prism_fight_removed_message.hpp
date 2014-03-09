//  Generated by desperion protocol_builder

#ifndef core_prism_fight_removed_message_hpp
#define core_prism_fight_removed_message_hpp

namespace protocol
{
    struct prism_fight_removed_message : dofus_unit
    {
        int16_t sub_area_id;
        
        int16_t id() const override
        { return 6453; } 
        
        prism_fight_removed_message(const int16_t & sub_area_id)
        {
            _data << sub_area_id;
        }
        
        prism_fight_removed_message(byte_buffer & data)
        {
            data >> sub_area_id;
        }
    };
}

#endif
