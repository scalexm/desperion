//  Generated by desperion protocol_builder

#ifndef core_challenge_result_message_hpp
#define core_challenge_result_message_hpp

namespace network
{
    struct challenge_result_message : dofus_unit
    {
        int16_t challenge_id;
        bool success;
        
        int16_t id() const override
        { return 6019; } 
        
        challenge_result_message(const int16_t & challenge_id, const bool & success)
        {
            _data << challenge_id;
            _data << success;
        }
        
        challenge_result_message(byte_buffer & data)
        {
            data >> challenge_id;
            data >> success;
        }
    };
}

#endif
