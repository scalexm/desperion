//  Generated by desperion protocol_builder

#ifndef core_achievement_details_request_message_hpp
#define core_achievement_details_request_message_hpp

namespace network
{
    struct achievement_details_request_message : dofus_unit
    {
        int16_t achievement_id;
        
        int16_t id() const override
        { return 6380; } 
        
        achievement_details_request_message(const int16_t & achievement_id)
        {
            _data << achievement_id;
        }
        
        achievement_details_request_message(byte_buffer & data)
        {
            data >> achievement_id;
        }
    };
}

#endif
