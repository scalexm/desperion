//  Generated by desperion protocol_builder

#ifndef core_prism_fight_swap_request_message_hpp
#define core_prism_fight_swap_request_message_hpp

namespace network
{
    struct prism_fight_swap_request_message : dofus_unit
    {
        int16_t sub_area_id;
        int32_t target_id;
        
        int16_t id() const override
        { return 5901; } 
        
        prism_fight_swap_request_message(const int16_t & sub_area_id, const int32_t & target_id)
        {
            _data << sub_area_id;
            _data << target_id;
        }
        
        prism_fight_swap_request_message(byte_buffer & data)
        {
            data >> sub_area_id;
            data >> target_id;
        }
    };
}

#endif
