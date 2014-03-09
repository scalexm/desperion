//  Generated by desperion protocol_builder

#ifndef core_acquaintance_search_message_hpp
#define core_acquaintance_search_message_hpp

namespace protocol
{
    struct acquaintance_search_message : dofus_unit
    {
        std::string nickname;
        
        int16_t id() const override
        { return 6144; } 
        
        acquaintance_search_message(const std::string & nickname)
        {
            _data << nickname;
        }
        
        acquaintance_search_message(byte_buffer & data)
        {
            data >> nickname;
        }
    };
}

#endif
