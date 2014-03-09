//  Generated by desperion protocol_builder

#ifndef core_skill_action_description_timed_hpp
#define core_skill_action_description_timed_hpp

namespace protocol
{
    struct skill_action_description_timed : skill_action_description
    {
        int8_t time;
        
        int16_t id() const override
        { return 103; } 
        
        skill_action_description_timed(const int16_t & skill_id, const int8_t & time) : skill_action_description { skill_id }
        {
            _data << time;
        }
        
        skill_action_description_timed(byte_buffer & data) : skill_action_description { data }
        {
            data >> time;
        }
    };
    
    using skill_action_description_timed_ptr = std::unique_ptr<skill_action_description_timed>;
}

#endif
