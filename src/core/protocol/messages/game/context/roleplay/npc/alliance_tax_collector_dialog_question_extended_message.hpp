//  Generated by desperion protocol_builder

#ifndef core_alliance_tax_collector_dialog_question_extended_message_hpp
#define core_alliance_tax_collector_dialog_question_extended_message_hpp

namespace protocol
{
    struct alliance_tax_collector_dialog_question_extended_message : tax_collector_dialog_question_extended_message
    {
        basic_named_alliance_informations_ptr alliance;
        
        int16_t id() const override
        { return 6445; } 
        
        alliance_tax_collector_dialog_question_extended_message(const int16_t & max_pods, const int16_t & prospecting, const int16_t & wisdom, const int8_t & tax_collectors_count, const int32_t & tax_collector_attack, const int32_t & kamas, const double & experience, const int32_t & pods, const int32_t & items_value, const basic_guild_informations_ptr & guild_info, const basic_named_alliance_informations_ptr & alliance) : tax_collector_dialog_question_extended_message { max_pods,prospecting,wisdom,tax_collectors_count,tax_collector_attack,kamas,experience,pods,items_value,guild_info }
        {
            _data << alliance->buffer();
        }
        
        alliance_tax_collector_dialog_question_extended_message(byte_buffer & data) : tax_collector_dialog_question_extended_message { data }
        {
            alliance = std::make_unique<basic_named_alliance_informations>(data);
        }
    };
}

#endif
