//  Generated by desperion protocol_builder

#ifndef core_tax_collector_dialog_question_basic_message_hpp
#define core_tax_collector_dialog_question_basic_message_hpp

namespace protocol
{
    struct tax_collector_dialog_question_basic_message : dofus_unit
    {
        basic_guild_informations_ptr guild_info;
        
        int16_t id() const override
        { return 5619; } 
        
        tax_collector_dialog_question_basic_message(const basic_guild_informations_ptr & guild_info)
        {
            _data << guild_info->buffer();
        }
        
        tax_collector_dialog_question_basic_message(byte_buffer & data)
        {
            guild_info = std::make_unique<basic_guild_informations>(data);
        }
    };
}

#endif
