//  Generated by desperion protocol_builder

#ifndef core_object_effect_date_hpp
#define core_object_effect_date_hpp

namespace protocol
{
    struct object_effect_date : object_effect
    {
        int16_t year;
        int16_t month;
        int16_t day;
        int16_t hour;
        int16_t minute;
        
        int16_t id() const override
        { return 72; } 
        
        object_effect_date(const int16_t & action_id, const int16_t & year, const int16_t & month, const int16_t & day, const int16_t & hour, const int16_t & minute) : object_effect { action_id }
        {
            _data << year;
            _data << month;
            _data << day;
            _data << hour;
            _data << minute;
        }
        
        object_effect_date(byte_buffer & data) : object_effect { data }
        {
            data >> year;
            data >> month;
            data >> day;
            data >> hour;
            data >> minute;
        }
    };
    
    using object_effect_date_ptr = std::unique_ptr<object_effect_date>;
}

#endif
