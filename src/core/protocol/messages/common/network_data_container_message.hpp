//  Generated by desperion protocol_builder

#ifndef core_network_data_container_message_hpp
#define core_network_data_container_message_hpp

namespace protocol
{
    struct network_data_container_message : dofus_unit
    {
        bytes_ptr content;
        
        int16_t id() const override
        { return 2; } 
        
        network_data_container_message(const bytes_ptr & content)
        {
            _data << content->buffer();
        }
        
        network_data_container_message(byte_buffer & data)
        {
            content = std::make_unique<bytes>(data);
        }
    };
}

#endif
