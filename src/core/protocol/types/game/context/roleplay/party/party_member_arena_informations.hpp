//  Generated by desperion protocol_builder

#ifndef core_party_member_arena_informations_hpp
#define core_party_member_arena_informations_hpp

namespace protocol
{
    struct party_member_arena_informations : party_member_informations
    {
        int16_t rank;
        
        int16_t id() const override
        { return 391; } 
        
        party_member_arena_informations(const int32_t & life_points, const int32_t & max_life_points, const int16_t & prospecting, const int8_t & regen_rate, const int16_t & initiative, const int8_t & alignment_side, const int16_t & world_x, const int16_t & world_y, const int32_t & map_id, const int16_t & sub_area_id, const player_status_ptr & status, const int8_t & breed, const bool & sex, const entity_look_ptr & entity_look, const int8_t & level, const std::string & name, const int32_t & id, const int16_t & rank) : party_member_informations { life_points,max_life_points,prospecting,regen_rate,initiative,alignment_side,world_x,world_y,map_id,sub_area_id,status,breed,sex,entity_look,level,name,id }
        {
            _data << rank;
        }
        
        party_member_arena_informations(byte_buffer & data) : party_member_informations { data }
        {
            data >> rank;
        }
    };
    
    using party_member_arena_informations_ptr = std::unique_ptr<party_member_arena_informations>;
}

#endif
