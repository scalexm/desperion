//  Generated by desperion protocol_builder

#ifndef d2fstream_speaking_items_trigger_hpp
#define d2fstream_speaking_items_trigger_hpp

namespace datacenter
{
    struct speaking_items_trigger : data_holder
    {
        int32_t triggers_id;
        std::vector<int32_t> text_ids;
        std::vector<int32_t> states;
        
        speaking_items_trigger() = default;
        
        speaking_items_trigger(const int32_t & triggers_id, const std::vector<int32_t> & text_ids, const std::vector<int32_t> & states) : triggers_id { triggers_id }, text_ids { text_ids }, states { states }
        {
        }
        
        speaking_items_trigger(data_object && data)
        {
            acquire(triggers_id, data.second.at("triggersId"));
            acquire(text_ids, data.second.at("textIds"));
            acquire(states, data.second.at("states"));
        }
        
        data_object to_d2o(const d2o_writer &);
    };

#ifdef d2fstream_d2o_writer_hpp
    data_object to_d2o(const d2o_writer & file)
    {
        data_object data;
        data.first = file.get_class_id_for_type<speaking_items_trigger>();
        release(triggers_id, data.second["triggersId"], file);
        release(text_ids, data.second["textIds"], file);
        release(states, data.second["states"], file);
        return data;
    }
#endif
}
#endif