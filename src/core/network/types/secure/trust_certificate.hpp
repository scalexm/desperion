//  Generated by desperion protocol_builder

#ifndef core_trust_certificate_hpp
#define core_trust_certificate_hpp

namespace network
{
    struct trust_certificate : dofus_unit
    {
        int32_t id;
        std::string hash;
        
        int16_t id() const override
        { return 377; } 
        
        trust_certificate(const int32_t & id, const std::string & hash)
        {
            _data << id;
            _data << hash;
        }
        
        trust_certificate(byte_buffer & data)
        {
            data >> id;
            data >> hash;
        }
    };
    
    using trust_certificate_ptr = std::unique_ptr<trust_certificate>;
}

#endif
