//  Generated by desperion protocol_builder

#ifndef core_human_option_alliance_hpp
#define core_human_option_alliance_hpp

namespace network
{
    struct human_option_alliance : human_option
    {
        alliance_informations_ptr alliance_informations;
        int8_t aggressable;
        
        int16_t id() const override
        { return 425; } 
        
        human_option_alliance(const alliance_informations_ptr & alliance_informations, const int8_t & aggressable)
        {
            _data << alliance_informations->buffer();
            _data << aggressable;
        }
        
        human_option_alliance(byte_buffer & data) : human_option { data }
        {
            alliance_informations = std::make_unique<alliance_informations>(data);
            data >> aggressable;
        }
    };
    
    using human_option_alliance_ptr = std::unique_ptr<human_option_alliance>;
}

#endif