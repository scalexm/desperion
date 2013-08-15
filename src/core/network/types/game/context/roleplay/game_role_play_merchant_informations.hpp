//  Generated by desperion protocol_builder

#ifndef core_game_role_play_merchant_informations_hpp
#define core_game_role_play_merchant_informations_hpp

namespace network
{
    struct game_role_play_merchant_informations : game_role_play_named_actor_informations
    {
        int32_t sell_type;
        std::vector<human_option_ptr> options;
        
        int16_t id() const override
        { return 129; } 
        
        game_role_play_merchant_informations(const std::string & name, const int32_t & contextual_id, const entity_look_ptr & look, const entity_disposition_informations_ptr & disposition, const int32_t & sell_type, const std::vector<human_option_ptr> & options) : game_role_play_named_actor_informations { name,contextual_id,look,disposition }
        {
            _data << sell_type;
            _data << static_cast<int16_t>(options.size());
            for (auto && i : options)
                _data << i->id() << i->buffer();
        }
        
        game_role_play_merchant_informations(byte_buffer & data) : game_role_play_named_actor_informations { data }
        {
            data >> sell_type;
            int16_t options_size;
            data >> options_size;
            options.resize(options_size);
            for (int16_t i = 0; i < options_size; ++i)
            {
                int16_t p;
                data >> p;
                options[i].reset(type_manager::get_human_option(p, data));
            }
        }
    };
    
    using game_role_play_merchant_informations_ptr = std::unique_ptr<game_role_play_merchant_informations>;
}

#endif
