//  Generated by desperion protocol_builder

#ifndef core_gold_item_hpp
#define core_gold_item_hpp

namespace network
{
    struct gold_item : item
    {
        int32_t sum;
        
        int16_t id() const override
        { return 123; } 
        
        gold_item(const int32_t & sum)
        {
            _data << sum;
        }
        
        gold_item(byte_buffer & data) : item { data }
        {
            data >> sum;
        }
    };
    
    using gold_item_ptr = std::unique_ptr<gold_item>;
}

#endif
