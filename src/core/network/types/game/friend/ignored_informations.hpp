//  Generated by desperion protocol_builder

#ifndef core_ignored_informations_hpp
#define core_ignored_informations_hpp

namespace network
{
    struct ignored_informations : abstract_contact_informations
    {
        
        int16_t id() const override
        { return 106; } 
        
        ignored_informations(const int32_t & account_id, const std::string & account_name) : abstract_contact_informations { account_id,account_name }
        {
        }
        
        ignored_informations(byte_buffer & data) : abstract_contact_informations { data }
        {
        }
    };
    
    using ignored_informations_ptr = std::unique_ptr<ignored_informations>;
}

#endif