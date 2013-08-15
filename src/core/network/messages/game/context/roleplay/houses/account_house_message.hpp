//  Generated by desperion protocol_builder

#ifndef core_account_house_message_hpp
#define core_account_house_message_hpp

namespace network
{
    struct account_house_message : dofus_unit
    {
        std::vector<account_house_informations_ptr> houses;
        
        int16_t id() const override
        { return 6315; } 
        
        account_house_message(const std::vector<account_house_informations_ptr> & houses)
        {
            _data << static_cast<int16_t>(houses.size());
            for (auto && i : houses)
                _data << i->buffer();
        }
        
        account_house_message(byte_buffer & data)
        {
            int16_t houses_size;
            data >> houses_size;
            houses.resize(houses_size);
            for (int16_t i = 0; i < houses_size; ++i)
                houses[i] = std::make_unique<account_house_informations>(data);
        }
    };
}

#endif
