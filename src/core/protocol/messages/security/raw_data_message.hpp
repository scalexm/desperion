//  Generated by desperion protocol_builder

#ifndef core_raw_data_message_hpp
#define core_raw_data_message_hpp

namespace protocol
{
    struct raw_data_message : dofus_unit
    {
        std::vector<int8_t> content;
        
        int16_t id() const override
        { return 6253; } 
        
        raw_data_message(const std::vector<int8_t> & content)
        {
            _data << content;
        }
        
        raw_data_message(byte_buffer & data)
        {
            data >> content;
        }
    };
}

#endif
