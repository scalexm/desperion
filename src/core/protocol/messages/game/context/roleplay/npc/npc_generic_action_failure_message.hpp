//  Generated by desperion protocol_builder

#ifndef core_npc_generic_action_failure_message_hpp
#define core_npc_generic_action_failure_message_hpp

namespace protocol
{
    struct npc_generic_action_failure_message : dofus_unit
    {
        
        int16_t id() const override
        { return 5900; } 
        
        npc_generic_action_failure_message()
        {
        }
        
        npc_generic_action_failure_message(byte_buffer & data)
        {
        }
    };
}

#endif
