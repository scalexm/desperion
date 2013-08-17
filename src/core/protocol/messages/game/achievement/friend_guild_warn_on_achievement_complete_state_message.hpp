//  Generated by desperion protocol_builder

#ifndef core_friend_guild_warn_on_achievement_complete_state_message_hpp
#define core_friend_guild_warn_on_achievement_complete_state_message_hpp

namespace network
{
    struct friend_guild_warn_on_achievement_complete_state_message : dofus_unit
    {
        bool enable;
        
        int16_t id() const override
        { return 6383; } 
        
        friend_guild_warn_on_achievement_complete_state_message(const bool & enable)
        {
            _data << enable;
        }
        
        friend_guild_warn_on_achievement_complete_state_message(byte_buffer & data)
        {
            data >> enable;
        }
    };
}

#endif
