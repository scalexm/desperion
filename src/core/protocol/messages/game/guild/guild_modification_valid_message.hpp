//  Generated by desperion protocol_builder

#ifndef core_guild_modification_valid_message_hpp
#define core_guild_modification_valid_message_hpp

namespace network
{
    struct guild_modification_valid_message : dofus_unit
    {
        std::string guild_name;
        guild_emblem_ptr guild_emblem;
        
        int16_t id() const override
        { return 6323; } 
        
        guild_modification_valid_message(const std::string & guild_name, const guild_emblem_ptr & guild_emblem)
        {
            _data << guild_name;
            _data << guild_emblem->buffer();
        }
        
        guild_modification_valid_message(byte_buffer & data)
        {
            data >> guild_name;
            guild_emblem = std::make_unique<guild_emblem>(data);
        }
    };
}

#endif