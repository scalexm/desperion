//  Generated by desperion protocol_builder

#ifndef core_game_context_actor_informations_hpp
#define core_game_context_actor_informations_hpp

namespace protocol
{
    struct game_context_actor_informations : dofus_unit
    {
        int32_t contextual_id;
        entity_look_ptr look;
        entity_disposition_informations_ptr disposition;
        
        int16_t id() const override
        { return 150; } 
        
        game_context_actor_informations(const int32_t & contextual_id, const entity_look_ptr & look, const entity_disposition_informations_ptr & disposition)
        {
            _data << contextual_id;
            _data << look->buffer();
            _data << disposition->id() << disposition->buffer();
        }
        
        game_context_actor_informations(byte_buffer & data)
        {
            data >> contextual_id;
            look = std::make_unique<entity_look>(data);
            int16_t disposition_id;
            data >> disposition_id;
            disposition.reset(type_manager::get_entity_disposition_informations(disposition_id, data));
        }
    };
    
    using game_context_actor_informations_ptr = std::unique_ptr<game_context_actor_informations>;
}

#endif
