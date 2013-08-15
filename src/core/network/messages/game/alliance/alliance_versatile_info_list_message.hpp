//  Generated by desperion protocol_builder

#ifndef core_alliance_versatile_info_list_message_hpp
#define core_alliance_versatile_info_list_message_hpp

namespace network
{
    struct alliance_versatile_info_list_message : dofus_unit
    {
        std::vector<alliance_versatile_informations_ptr> alliances;
        
        int16_t id() const override
        { return 6436; } 
        
        alliance_versatile_info_list_message(const std::vector<alliance_versatile_informations_ptr> & alliances)
        {
            _data << static_cast<int16_t>(alliances.size());
            for (auto && i : alliances)
                _data << i->buffer();
        }
        
        alliance_versatile_info_list_message(byte_buffer & data)
        {
            int16_t alliances_size;
            data >> alliances_size;
            alliances.resize(alliances_size);
            for (int16_t i = 0; i < alliances_size; ++i)
                alliances[i] = std::make_unique<alliance_versatile_informations>(data);
        }
    };
}

#endif
