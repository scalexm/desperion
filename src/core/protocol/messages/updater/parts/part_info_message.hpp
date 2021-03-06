//  Generated by desperion protocol_builder

#ifndef core_part_info_message_hpp
#define core_part_info_message_hpp

namespace protocol
{
    struct part_info_message : dofus_unit
    {
        content_part_ptr part;
        float_ptr installation_percent;
        
        int16_t id() const override
        { return 1508; } 
        
        part_info_message(const content_part_ptr & part, const float_ptr & installation_percent)
        {
            _data << part->buffer();
            _data << installation_percent->buffer();
        }
        
        part_info_message(byte_buffer & data)
        {
            part = std::make_unique<content_part>(data);
            installation_percent = std::make_unique<float>(data);
        }
    };
}

#endif
