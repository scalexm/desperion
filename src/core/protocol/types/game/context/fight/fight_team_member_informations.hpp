//  Generated by desperion protocol_builder

#ifndef core_fight_team_member_informations_hpp
#define core_fight_team_member_informations_hpp

namespace network
{
    struct fight_team_member_informations : dofus_unit
    {
        int32_t id;
        
        int16_t id() const override
        { return 44; } 
        
        fight_team_member_informations(const int32_t & id)
        {
            _data << id;
        }
        
        fight_team_member_informations(byte_buffer & data)
        {
            data >> id;
        }
    };
    
    using fight_team_member_informations_ptr = std::unique_ptr<fight_team_member_informations>;
}

#endif
