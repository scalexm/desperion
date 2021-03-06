//  Generated by desperion protocol_builder

#ifndef d2fstream_appearance_hpp
#define d2fstream_appearance_hpp

namespace datacenter
{
    struct appearance : data_holder
    {
        int32_t id;
        int32_t type;
        std::string data;
        
        appearance() = default;
        
        appearance(const int32_t & id, const int32_t & type, const std::string & data) : id { id }, type { type }, data { data }
        {
        }
        
        appearance(data_object && data)
        {
            acquire(id, data.second.at("id"));
            acquire(type, data.second.at("type"));
            acquire(data, data.second.at("data"));
        }
        
        data_object to_d2o(const d2o_writer &);
    };

#ifdef d2fstream_d2o_writer_hpp
    data_object to_d2o(const d2o_writer & file)
    {
        data_object data;
        data.first = file.get_class_id_for_type<appearance>();
        release(id, data.second["id"], file);
        release(type, data.second["type"], file);
        release(data, data.second["data"], file);
        return data;
    }
#endif
}
#endif