//  Generated by desperion protocol_builder

#ifndef core_version_hpp
#define core_version_hpp

namespace protocol
{
    struct version : dofus_unit
    {
        int8_t major;
        int8_t minor;
        int8_t release;
        int32_t revision;
        int8_t patch;
        int8_t build_type;
        
        int16_t id() const override
        { return 11; } 
        
        version(const int8_t & major, const int8_t & minor, const int8_t & release, const int32_t & revision, const int8_t & patch, const int8_t & build_type)
        {
            _data << major;
            _data << minor;
            _data << release;
            _data << revision;
            _data << patch;
            _data << build_type;
        }
        
        version(byte_buffer & data)
        {
            data >> major;
            data >> minor;
            data >> release;
            data >> revision;
            data >> patch;
            data >> build_type;
        }
    };
    
    using version_ptr = std::unique_ptr<version>;
}

#endif
