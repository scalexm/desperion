//  Generated by desperion protocol_builder

#ifndef core_server_session_constant_integer_hpp
#define core_server_session_constant_integer_hpp

namespace network
{
    struct server_session_constant_integer : server_session_constant
    {
        int32_t value;
        
        int16_t id() const override
        { return 433; } 
        
        server_session_constant_integer(const int16_t & id, const int32_t & value) : server_session_constant { id }
        {
            _data << value;
        }
        
        server_session_constant_integer(byte_buffer & data) : server_session_constant { data }
        {
            data >> value;
        }
    };
    
    using server_session_constant_integer_ptr = std::unique_ptr<server_session_constant_integer>;
}

#endif
