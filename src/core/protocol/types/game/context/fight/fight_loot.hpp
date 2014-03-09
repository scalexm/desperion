//  Generated by desperion protocol_builder

#ifndef core_fight_loot_hpp
#define core_fight_loot_hpp

namespace protocol
{
    struct fight_loot : dofus_unit
    {
        std::vector<int16_t> objects;
        int32_t kamas;
        
        int16_t id() const override
        { return 41; } 
        
        fight_loot(const std::vector<int16_t> & objects, const int32_t & kamas)
        {
            _data << static_cast<int16_t>(objects.size());
            for (auto && i : objects)
                _data << i;
            _data << kamas;
        }
        
        fight_loot(byte_buffer & data)
        {
            int16_t objects_size;
            data >> objects_size;
            objects.resize(objects_size);
            for (int16_t i = 0; i < objects_size; ++i)
                data >> objects[i];
            data >> kamas;
        }
    };
    
    using fight_loot_ptr = std::unique_ptr<fight_loot>;
}

#endif
