//  Generated by desperion protocol_builder

#ifndef d2fstream_group_item_criterion_hpp
#define d2fstream_group_item_criterion_hpp

namespace datacenter
{
    struct group_item_criterion : data_holder
    {
        
        group_item_criterion()
        {
        }
        
        group_item_criterion(data_object && data)
        {
        }
        
        data_object to_d2o(const d2o_writer &);
    };

#ifdef d2fstream_d2o_writer_hpp
    data_object to_d2o(const d2o_writer & file)
    {
        data_object data;
        data.first = file.get_class_id_for_type<group_item_criterion>();
        return data;
    }
#endif
}
#endif