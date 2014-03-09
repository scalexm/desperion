//  Generated by desperion protocol_builder

#ifndef core_shortcut_hpp
#define core_shortcut_hpp

namespace protocol
{
    struct shortcut : dofus_unit
    {
        int32_t slot;
        
        int16_t id() const override
        { return 369; } 
        
        shortcut(const int32_t & slot)
        {
            _data << slot;
        }
        
        shortcut(byte_buffer & data)
        {
            data >> slot;
        }
    };
    
    using shortcut_ptr = std::unique_ptr<shortcut>;
}

#endif
