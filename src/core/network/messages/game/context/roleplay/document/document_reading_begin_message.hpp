//  Generated by desperion protocol_builder

#ifndef core_document_reading_begin_message_hpp
#define core_document_reading_begin_message_hpp

namespace network
{
    struct document_reading_begin_message : dofus_unit
    {
        int16_t document_id;
        
        int16_t id() const override
        { return 5675; } 
        
        document_reading_begin_message(const int16_t & document_id)
        {
            _data << document_id;
        }
        
        document_reading_begin_message(byte_buffer & data)
        {
            data >> document_id;
        }
    };
}

#endif