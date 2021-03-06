//  Generated by desperion protocol_builder

#ifndef core_prism_fight_join_leave_request_message_hpp
#define core_prism_fight_join_leave_request_message_hpp

namespace protocol
{
    struct prism_fight_join_leave_request_message : dofus_unit
    {
        int16_t sub_area_id;
        bool join;
        
        int16_t id() const override
        { return 5843; } 
        
        prism_fight_join_leave_request_message(const int16_t & sub_area_id, const bool & join)
        {
            _data << sub_area_id;
            _data << join;
        }
        
        prism_fight_join_leave_request_message(byte_buffer & data)
        {
            data >> sub_area_id;
            data >> join;
        }
    };
}

#endif
