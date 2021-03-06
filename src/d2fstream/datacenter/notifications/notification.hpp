//  Generated by desperion protocol_builder

#ifndef d2fstream_notification_hpp
#define d2fstream_notification_hpp

namespace datacenter
{
    struct notification : data_holder
    {
        int32_t id;
        int32_t title_id;
        int32_t message_id;
        int32_t icon_id;
        int32_t type_id;
        std::string trigger;
        
        notification() = default;
        
        notification(const int32_t & id, const int32_t & title_id, const int32_t & message_id, const int32_t & icon_id, const int32_t & type_id, const std::string & trigger) : id { id }, title_id { title_id }, message_id { message_id }, icon_id { icon_id }, type_id { type_id }, trigger { trigger }
        {
        }
        
        notification(data_object && data)
        {
            acquire(id, data.second.at("id"));
            acquire(title_id, data.second.at("titleId"));
            acquire(message_id, data.second.at("messageId"));
            acquire(icon_id, data.second.at("iconId"));
            acquire(type_id, data.second.at("typeId"));
            acquire(trigger, data.second.at("trigger"));
        }
        
        data_object to_d2o(const d2o_writer &);
    };

#ifdef d2fstream_d2o_writer_hpp
    data_object to_d2o(const d2o_writer & file)
    {
        data_object data;
        data.first = file.get_class_id_for_type<notification>();
        release(id, data.second["id"], file);
        release(title_id, data.second["titleId"], file);
        release(message_id, data.second["messageId"], file);
        release(icon_id, data.second["iconId"], file);
        release(type_id, data.second["typeId"], file);
        release(trigger, data.second["trigger"], file);
        return data;
    }
#endif
}
#endif