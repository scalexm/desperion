//  Generated by desperion protocol_builder

#ifndef core_paddock_private_informations_hpp
#define core_paddock_private_informations_hpp

namespace network
{
    struct paddock_private_informations : paddock_abandonned_informations
    {
        guild_informations_ptr guild_info;
        
        int16_t id() const override
        { return 131; } 
        
        paddock_private_informations(const int32_t & guild_id, const int32_t & price, const bool & locked, const int16_t & max_outdoor_mount, const int16_t & max_items, const guild_informations_ptr & guild_info) : paddock_abandonned_informations { guild_id,price,locked,max_outdoor_mount,max_items }
        {
            _data << guild_info->buffer();
        }
        
        paddock_private_informations(byte_buffer & data) : paddock_abandonned_informations { data }
        {
            guild_info = std::make_unique<guild_informations>(data);
        }
    };
    
    using paddock_private_informations_ptr = std::unique_ptr<paddock_private_informations>;
}

#endif
