//  Generated by desperion protocol_builder

#ifndef core_living_object_message_message_hpp
#define core_living_object_message_message_hpp

namespace protocol
{
    struct living_object_message_message : dofus_unit
    {
        int16_t msg_id;
        unsigned_int_ptr time_stamp;
        std::string owner;
        unsigned_int_ptr object_generic_id;
        
        int16_t id() const override
        { return 6065; } 
        
        living_object_message_message(const int16_t & msg_id, const unsigned_int_ptr & time_stamp, const std::string & owner, const unsigned_int_ptr & object_generic_id)
        {
            _data << msg_id;
            _data << time_stamp->buffer();
            _data << owner;
            _data << object_generic_id->buffer();
        }
        
        living_object_message_message(byte_buffer & data)
        {
            data >> msg_id;
            time_stamp = std::make_unique<unsigned_int>(data);
            data >> owner;
            object_generic_id = std::make_unique<unsigned_int>(data);
        }
    };
}

#endif
