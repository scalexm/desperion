//  Generated by desperion protocol_builder

#ifndef core_download_part_message_hpp
#define core_download_part_message_hpp

namespace network
{
    struct download_part_message : dofus_unit
    {
        std::string id;
        
        int16_t id() const override
        { return 1503; } 
        
        download_part_message(const std::string & id)
        {
            _data << id;
        }
        
        download_part_message(byte_buffer & data)
        {
            data >> id;
        }
    };
}

#endif
