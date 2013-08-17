//  Generated by desperion protocol_builder

#ifndef core_quest_active_detailed_informations_hpp
#define core_quest_active_detailed_informations_hpp

namespace network
{
    struct quest_active_detailed_informations : quest_active_informations
    {
        int16_t step_id;
        std::vector<quest_objective_informations_ptr> objectives;
        
        int16_t id() const override
        { return 382; } 
        
        quest_active_detailed_informations(const int16_t & quest_id, const int16_t & step_id, const std::vector<quest_objective_informations_ptr> & objectives) : quest_active_informations { quest_id }
        {
            _data << step_id;
            _data << static_cast<int16_t>(objectives.size());
            for (auto && i : objectives)
                _data << i->id() << i->buffer();
        }
        
        quest_active_detailed_informations(byte_buffer & data) : quest_active_informations { data }
        {
            data >> step_id;
            int16_t objectives_size;
            data >> objectives_size;
            objectives.resize(objectives_size);
            for (int16_t i = 0; i < objectives_size; ++i)
            {
                int16_t p;
                data >> p;
                objectives[i].reset(type_manager::get_quest_objective_informations(p, data));
            }
        }
    };
    
    using quest_active_detailed_informations_ptr = std::unique_ptr<quest_active_detailed_informations>;
}

#endif
