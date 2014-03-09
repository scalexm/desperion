//  Generated by desperion protocol_builder

#ifndef core_achievement_objective_hpp
#define core_achievement_objective_hpp

namespace protocol
{
    struct achievement_objective : dofus_unit
    {
        int32_t id;
        int16_t max_value;
        
        int16_t id() const override
        { return 404; } 
        
        achievement_objective(const int32_t & id, const int16_t & max_value)
        {
            _data << id;
            _data << max_value;
        }
        
        achievement_objective(byte_buffer & data)
        {
            data >> id;
            data >> max_value;
        }
    };
    
    using achievement_objective_ptr = std::unique_ptr<achievement_objective>;
}

#endif
