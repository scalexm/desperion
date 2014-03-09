//  Generated by desperion protocol_builder

#ifndef core_guild_house_update_information_message_hpp
#define core_guild_house_update_information_message_hpp

namespace protocol
{
    struct guild_house_update_information_message : dofus_unit
    {
        house_informations_for_guild_ptr houses_informations;
        
        int16_t id() const override
        { return 6181; } 
        
        guild_house_update_information_message(const house_informations_for_guild_ptr & houses_informations)
        {
            _data << houses_informations->buffer();
        }
        
        guild_house_update_information_message(byte_buffer & data)
        {
            houses_informations = std::make_unique<house_informations_for_guild>(data);
        }
    };
}

#endif
