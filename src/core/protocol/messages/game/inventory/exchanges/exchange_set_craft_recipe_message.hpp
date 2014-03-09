//  Generated by desperion protocol_builder

#ifndef core_exchange_set_craft_recipe_message_hpp
#define core_exchange_set_craft_recipe_message_hpp

namespace protocol
{
    struct exchange_set_craft_recipe_message : dofus_unit
    {
        int16_t object_g_i_d;
        
        int16_t id() const override
        { return 6389; } 
        
        exchange_set_craft_recipe_message(const int16_t & object_g_i_d)
        {
            _data << object_g_i_d;
        }
        
        exchange_set_craft_recipe_message(byte_buffer & data)
        {
            data >> object_g_i_d;
        }
    };
}

#endif
