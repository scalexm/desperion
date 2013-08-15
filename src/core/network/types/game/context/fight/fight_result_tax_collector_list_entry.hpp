//  Generated by desperion protocol_builder

#ifndef core_fight_result_tax_collector_list_entry_hpp
#define core_fight_result_tax_collector_list_entry_hpp

namespace network
{
    struct fight_result_tax_collector_list_entry : fight_result_fighter_list_entry
    {
        int8_t level;
        basic_guild_informations_ptr guild_info;
        int32_t experience_for_guild;
        
        int16_t id() const override
        { return 84; } 
        
        fight_result_tax_collector_list_entry(const int32_t & id, const bool & alive, const int16_t & outcome, const fight_loot_ptr & rewards, const int8_t & level, const basic_guild_informations_ptr & guild_info, const int32_t & experience_for_guild) : fight_result_fighter_list_entry { id,alive,outcome,rewards }
        {
            _data << level;
            _data << guild_info->buffer();
            _data << experience_for_guild;
        }
        
        fight_result_tax_collector_list_entry(byte_buffer & data) : fight_result_fighter_list_entry { data }
        {
            data >> level;
            guild_info = std::make_unique<basic_guild_informations>(data);
            data >> experience_for_guild;
        }
    };
    
    using fight_result_tax_collector_list_entry_ptr = std::unique_ptr<fight_result_tax_collector_list_entry>;
}

#endif
