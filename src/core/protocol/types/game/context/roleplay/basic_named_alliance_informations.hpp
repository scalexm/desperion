//  Generated by desperion protocol_builder

#ifndef core_basic_named_alliance_informations_hpp
#define core_basic_named_alliance_informations_hpp

namespace network
{
    struct basic_named_alliance_informations : basic_alliance_informations
    {
        std::string alliance_name;
        
        int16_t id() const override
        { return 418; } 
        
        basic_named_alliance_informations(const int32_t & alliance_id, const std::string & alliance_tag, const std::string & alliance_name) : basic_alliance_informations { alliance_id,alliance_tag }
        {
            _data << alliance_name;
        }
        
        basic_named_alliance_informations(byte_buffer & data) : basic_alliance_informations { data }
        {
            data >> alliance_name;
        }
    };
    
    using basic_named_alliance_informations_ptr = std::unique_ptr<basic_named_alliance_informations>;
}

#endif