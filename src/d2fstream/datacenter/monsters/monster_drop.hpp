//  Generated by desperion protocol_builder

#ifndef d2fstream_monster_drop_hpp
#define d2fstream_monster_drop_hpp

namespace datacenter
{
    struct monster_drop : data_holder
    {
        int32_t drop_id;
        int32_t monster_id;
        int32_t object_id;
        double percent_drop_for_grade_1;
        double percent_drop_for_grade_2;
        double percent_drop_for_grade_3;
        double percent_drop_for_grade_4;
        double percent_drop_for_grade_5;
        int32_t count;
        int32_t find_ceil;
        bool has_criteria;
        
        monster_drop() = default;
        
        monster_drop(const int32_t & drop_id, const int32_t & monster_id, const int32_t & object_id, const double & percent_drop_for_grade_1, const double & percent_drop_for_grade_2, const double & percent_drop_for_grade_3, const double & percent_drop_for_grade_4, const double & percent_drop_for_grade_5, const int32_t & count, const int32_t & find_ceil, const bool & has_criteria) : drop_id { drop_id }, monster_id { monster_id }, object_id { object_id }, percent_drop_for_grade_1 { percent_drop_for_grade_1 }, percent_drop_for_grade_2 { percent_drop_for_grade_2 }, percent_drop_for_grade_3 { percent_drop_for_grade_3 }, percent_drop_for_grade_4 { percent_drop_for_grade_4 }, percent_drop_for_grade_5 { percent_drop_for_grade_5 }, count { count }, find_ceil { find_ceil }, has_criteria { has_criteria }
        {
        }
        
        monster_drop(data_object && data)
        {
            acquire(drop_id, data.second.at("dropId"));
            acquire(monster_id, data.second.at("monsterId"));
            acquire(object_id, data.second.at("objectId"));
            acquire(percent_drop_for_grade_1, data.second.at("percentDropForGrade1"));
            acquire(percent_drop_for_grade_2, data.second.at("percentDropForGrade2"));
            acquire(percent_drop_for_grade_3, data.second.at("percentDropForGrade3"));
            acquire(percent_drop_for_grade_4, data.second.at("percentDropForGrade4"));
            acquire(percent_drop_for_grade_5, data.second.at("percentDropForGrade5"));
            acquire(count, data.second.at("count"));
            acquire(find_ceil, data.second.at("findCeil"));
            acquire(has_criteria, data.second.at("hasCriteria"));
        }
        
        data_object to_d2o(const d2o_writer &);
    };

#ifdef d2fstream_d2o_writer_hpp
    data_object to_d2o(const d2o_writer & file)
    {
        data_object data;
        data.first = file.get_class_id_for_type<monster_drop>();
        release(drop_id, data.second["dropId"], file);
        release(monster_id, data.second["monsterId"], file);
        release(object_id, data.second["objectId"], file);
        release(percent_drop_for_grade_1, data.second["percentDropForGrade1"], file);
        release(percent_drop_for_grade_2, data.second["percentDropForGrade2"], file);
        release(percent_drop_for_grade_3, data.second["percentDropForGrade3"], file);
        release(percent_drop_for_grade_4, data.second["percentDropForGrade4"], file);
        release(percent_drop_for_grade_5, data.second["percentDropForGrade5"], file);
        release(count, data.second["count"], file);
        release(find_ceil, data.second["findCeil"], file);
        release(has_criteria, data.second["hasCriteria"], file);
        return data;
    }
#endif
}
#endif