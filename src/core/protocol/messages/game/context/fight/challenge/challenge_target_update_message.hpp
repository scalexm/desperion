//  Generated by desperion protocol_builder

#ifndef core_challenge_target_update_message_hpp
#define core_challenge_target_update_message_hpp

namespace protocol
{
    struct challenge_target_update_message : dofus_unit
    {
        int16_t challenge_id;
        int32_t target_id;
        
        int16_t id() const override
        { return 6123; } 
        
        challenge_target_update_message(const int16_t & challenge_id, const int32_t & target_id)
        {
            _data << challenge_id;
            _data << target_id;
        }
        
        challenge_target_update_message(byte_buffer & data)
        {
            data >> challenge_id;
            data >> target_id;
        }
    };
}

#endif
