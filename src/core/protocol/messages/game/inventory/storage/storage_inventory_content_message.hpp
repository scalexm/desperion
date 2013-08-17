//  Generated by desperion protocol_builder

#ifndef core_storage_inventory_content_message_hpp
#define core_storage_inventory_content_message_hpp

namespace network
{
    struct storage_inventory_content_message : inventory_content_message
    {
        
        int16_t id() const override
        { return 5646; } 
        
        storage_inventory_content_message(const std::vector<object_item_ptr> & objects, const int32_t & kamas) : inventory_content_message { objects,kamas }
        {
        }
        
        storage_inventory_content_message(byte_buffer & data) : inventory_content_message { data }
        {
        }
    };
}

#endif