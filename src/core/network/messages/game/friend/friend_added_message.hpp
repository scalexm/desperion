//  Generated by desperion protocol_builder

#ifndef core_friend_added_message_hpp
#define core_friend_added_message_hpp

namespace network
{
    struct friend_added_message : dofus_unit
    {
        friend_informations_ptr friend_added;
        
        int16_t id() const override
        { return 5599; } 
        
        friend_added_message(const friend_informations_ptr & friend_added)
        {
            _data << friend_added->id() << friend_added->buffer();
        }
        
        friend_added_message(byte_buffer & data)
        {
            int16_t friend_added_id;
            data >> friend_added_id;
            friend_added.reset(type_manager::get_friend_informations(friend_added_id, data));
        }
    };
}

#endif
