//  Generated by desperion protocol_builder

#ifndef core_check_file_message_hpp
#define core_check_file_message_hpp

namespace protocol
{
    struct check_file_message : dofus_unit
    {
        std::string filename_hash;
        int8_t type;
        std::string value;
        
        int16_t id() const override
        { return 6156; } 
        
        check_file_message(const std::string & filename_hash, const int8_t & type, const std::string & value)
        {
            _data << filename_hash;
            _data << type;
            _data << value;
        }
        
        check_file_message(byte_buffer & data)
        {
            data >> filename_hash;
            data >> type;
            data >> value;
        }
    };
}

#endif
