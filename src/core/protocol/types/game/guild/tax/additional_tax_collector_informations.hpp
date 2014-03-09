//  Generated by desperion protocol_builder

#ifndef core_additional_tax_collector_informations_hpp
#define core_additional_tax_collector_informations_hpp

namespace protocol
{
    struct additional_tax_collector_informations : dofus_unit
    {
        std::string collector_caller_name;
        int32_t date;
        
        int16_t id() const override
        { return 165; } 
        
        additional_tax_collector_informations(const std::string & collector_caller_name, const int32_t & date)
        {
            _data << collector_caller_name;
            _data << date;
        }
        
        additional_tax_collector_informations(byte_buffer & data)
        {
            data >> collector_caller_name;
            data >> date;
        }
    };
    
    using additional_tax_collector_informations_ptr = std::unique_ptr<additional_tax_collector_informations>;
}

#endif
