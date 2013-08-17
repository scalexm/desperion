//  Generated by desperion protocol_builder

#ifndef core_alignment_rank_update_message_hpp
#define core_alignment_rank_update_message_hpp

namespace network
{
    struct alignment_rank_update_message : dofus_unit
    {
        int8_t alignment_rank;
        bool verbose;
        
        int16_t id() const override
        { return 6058; } 
        
        alignment_rank_update_message(const int8_t & alignment_rank, const bool & verbose)
        {
            _data << alignment_rank;
            _data << verbose;
        }
        
        alignment_rank_update_message(byte_buffer & data)
        {
            data >> alignment_rank;
            data >> verbose;
        }
    };
}

#endif
