//  Generated by desperion protocol_builder

#ifndef core_paddock_buyable_informations_hpp
#define core_paddock_buyable_informations_hpp

namespace network
{
    struct paddock_buyable_informations : paddock_informations
    {
        int32_t price;
        bool locked;
        
        int16_t id() const override
        { return 130; } 
        
        paddock_buyable_informations(const int16_t & max_outdoor_mount, const int16_t & max_items, const int32_t & price, const bool & locked) : paddock_informations { max_outdoor_mount,max_items }
        {
            _data << price;
            _data << locked;
        }
        
        paddock_buyable_informations(byte_buffer & data) : paddock_informations { data }
        {
            data >> price;
            data >> locked;
        }
    };
    
    using paddock_buyable_informations_ptr = std::unique_ptr<paddock_buyable_informations>;
}

#endif
