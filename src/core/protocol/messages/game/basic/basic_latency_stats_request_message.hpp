//  Generated by desperion protocol_builder

#ifndef core_basic_latency_stats_request_message_hpp
#define core_basic_latency_stats_request_message_hpp

namespace network
{
    struct basic_latency_stats_request_message : dofus_unit
    {
        
        int16_t id() const override
        { return 5816; } 
        
        basic_latency_stats_request_message()
        {
        }
        
        basic_latency_stats_request_message(byte_buffer & data)
        {
        }
    };
}

#endif
