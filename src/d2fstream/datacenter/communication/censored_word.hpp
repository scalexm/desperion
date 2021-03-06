//  Generated by desperion protocol_builder

#ifndef d2fstream_censored_word_hpp
#define d2fstream_censored_word_hpp

namespace datacenter
{
    struct censored_word : data_holder
    {
        int32_t id;
        int32_t list_id;
        std::string language;
        std::string word;
        bool deep_looking;
        
        censored_word() = default;
        
        censored_word(const int32_t & id, const int32_t & list_id, const std::string & language, const std::string & word, const bool & deep_looking) : id { id }, list_id { list_id }, language { language }, word { word }, deep_looking { deep_looking }
        {
        }
        
        censored_word(data_object && data)
        {
            acquire(id, data.second.at("id"));
            acquire(list_id, data.second.at("listId"));
            acquire(language, data.second.at("language"));
            acquire(word, data.second.at("word"));
            acquire(deep_looking, data.second.at("deepLooking"));
        }
        
        data_object to_d2o(const d2o_writer &);
    };

#ifdef d2fstream_d2o_writer_hpp
    data_object to_d2o(const d2o_writer & file)
    {
        data_object data;
        data.first = file.get_class_id_for_type<censored_word>();
        release(id, data.second["id"], file);
        release(list_id, data.second["listId"], file);
        release(language, data.second["language"], file);
        release(word, data.second["word"], file);
        release(deep_looking, data.second["deepLooking"], file);
        return data;
    }
#endif
}
#endif