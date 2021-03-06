//  Generated by desperion protocol_builder

#ifndef core_stated_element_hpp
#define core_stated_element_hpp

namespace protocol
{
    struct stated_element : dofus_unit
    {
        int32_t element_id;
        int16_t element_cell_id;
        int32_t element_state;
        
        int16_t id() const override
        { return 108; } 
        
        stated_element(const int32_t & element_id, const int16_t & element_cell_id, const int32_t & element_state)
        {
            _data << element_id;
            _data << element_cell_id;
            _data << element_state;
        }
        
        stated_element(byte_buffer & data)
        {
            data >> element_id;
            data >> element_cell_id;
            data >> element_state;
        }
    };
    
    using stated_element_ptr = std::unique_ptr<stated_element>;
}

#endif
