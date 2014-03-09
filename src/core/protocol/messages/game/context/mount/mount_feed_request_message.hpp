//  Generated by desperion protocol_builder

#ifndef core_mount_feed_request_message_hpp
#define core_mount_feed_request_message_hpp

namespace protocol
{
    struct mount_feed_request_message : dofus_unit
    {
        double mount_uid;
        int8_t mount_location;
        int32_t mount_food_uid;
        int32_t quantity;
        
        int16_t id() const override
        { return 6189; } 
        
        mount_feed_request_message(const double & mount_uid, const int8_t & mount_location, const int32_t & mount_food_uid, const int32_t & quantity)
        {
            _data << mount_uid;
            _data << mount_location;
            _data << mount_food_uid;
            _data << quantity;
        }
        
        mount_feed_request_message(byte_buffer & data)
        {
            data >> mount_uid;
            data >> mount_location;
            data >> mount_food_uid;
            data >> quantity;
        }
    };
}

#endif
