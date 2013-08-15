//  Generated by desperion protocol_builder

#ifndef core_basic_pong_message_hpp
#define core_basic_pong_message_hpp

namespace network
{
    struct basic_pong_message : dofus_unit
    {
        bool quiet;
        
        int16_t id() const override
        { return 183; } 
        
        basic_pong_message(const bool & quiet)
        {
            _data << quiet;
        }
        
        basic_pong_message(byte_buffer & data)
        {
            data >> quiet;
        }
    };
}

#endif
