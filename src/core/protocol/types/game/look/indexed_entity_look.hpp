//  Generated by desperion protocol_builder

#ifndef core_indexed_entity_look_hpp
#define core_indexed_entity_look_hpp

namespace protocol
{
    struct indexed_entity_look : dofus_unit
    {
        entity_look_ptr look;
        int8_t index;
        
        int16_t id() const override
        { return 405; } 
        
        indexed_entity_look(const entity_look_ptr & look, const int8_t & index)
        {
            _data << look->buffer();
            _data << index;
        }
        
        indexed_entity_look(byte_buffer & data)
        {
            look = std::make_unique<entity_look>(data);
            data >> index;
        }
    };
    
    using indexed_entity_look_ptr = std::unique_ptr<indexed_entity_look>;
}

#endif
