//  Generated by desperion protocol_builder

#ifndef core_achievement_started_objective_hpp
#define core_achievement_started_objective_hpp

namespace protocol
{
    struct achievement_started_objective : achievement_objective
    {
        int16_t value;
        
        int16_t id() const override
        { return 402; } 
        
        achievement_started_objective(const int32_t & id, const int16_t & max_value, const int16_t & value) : achievement_objective { id,max_value }
        {
            _data << value;
        }
        
        achievement_started_objective(byte_buffer & data) : achievement_objective { data }
        {
            data >> value;
        }
    };
    
    using achievement_started_objective_ptr = std::unique_ptr<achievement_started_objective>;
}

#endif
