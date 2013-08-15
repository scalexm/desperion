//  Generated by desperion protocol_builder

#ifndef core_map_running_fight_details_request_message_hpp
#define core_map_running_fight_details_request_message_hpp

namespace network
{
    struct map_running_fight_details_request_message : dofus_unit
    {
        int32_t fight_id;
        
        int16_t id() const override
        { return 5750; } 
        
        map_running_fight_details_request_message(const int32_t & fight_id)
        {
            _data << fight_id;
        }
        
        map_running_fight_details_request_message(byte_buffer & data)
        {
            data >> fight_id;
        }
    };
}

#endif