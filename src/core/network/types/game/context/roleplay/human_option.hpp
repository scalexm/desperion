//  Generated by desperion protocol_builder

#ifndef core_human_option_hpp
#define core_human_option_hpp

namespace network
{
    struct human_option : dofus_unit
    {
        
        int16_t id() const override
        { return 406; } 
        
        human_option()
        {
        }
        
        human_option(byte_buffer & data)
        {
        }
    };
    
    using human_option_ptr = std::unique_ptr<human_option>;
}

#endif
