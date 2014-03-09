//
//  main.cpp
//  protocol_builder
//
//  Created by Alexandre Martin on 05/08/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#include "enum_file.hpp"
#include "output_helper.hpp"
#include "network_file.hpp"
#include "datacenter_file.hpp"
#include <iostream>
#include <boost/filesystem.hpp>
#include <sstream>

namespace fs = boost::filesystem;

////////////

/*
 boost doesn't seem to support relative path computing, so using this one instead.
 Found this here: https://svn.boost.org/trac/boost/ticket/5897
 */

namespace boost { namespace filesystem {
    template < >
    path& path::append< typename path::iterator >(typename path::iterator begin,
                                                  typename path::iterator end,
                                                  const codecvt_type& cvt)
    {
        for( ; begin != end ; ++begin )
            *this /= *begin;
        return *this;
    }
} }

fs::path make_relative(fs::path a_From, fs::path a_To)
{
    a_From = fs::absolute(a_From); a_To = fs::absolute(a_To);
    fs::path ret;
    fs::path::const_iterator itrFrom(a_From.begin()), itrTo(a_To.begin());
    // Find common base
    for (fs::path::const_iterator toEnd(a_To.end()), fromEnd(a_From.end());
        itrFrom != fromEnd && itrTo != toEnd && *itrFrom == *itrTo; ++itrFrom, ++itrTo);
    // Navigate backwards in directory to reach previously found base
    for (fs::path::const_iterator fromEnd(a_From.end());
         itrFrom != fromEnd; ++itrFrom)
    {
        if( (*itrFrom) != "." )
            ret /= "..";
    }
    // Now navigate down the directory branch
    ret.append( itrTo, a_To.end() );
    return ret;
}

////////////

void create(const fs::path & path)
{
    if (!fs::exists(path)
        || !fs::is_directory(path))
        fs::create_directory(path);
}

void make_cpp_file(const std::string & content, const fs::path & path)
{
    std::ofstream f { path.string() };
    f << content;
}

fs::path compute(const fs::path & local, const fs::path & protocol, const fs::path & path)
{
    auto complete_path = local / (make_relative(protocol, path));
    return complete_path;
}

template<class T>
void retrieve(std::unordered_map<std::string, T> & files,
              std::unordered_map<std::string, fs::path> & paths,
              const fs::path & local, const fs::path & protocol, const std::string & folder)
{
    for (fs::recursive_directory_iterator it { protocol / folder };
         it != fs::recursive_directory_iterator { }; ++it)
    {
        if (!fs::is_regular_file(it->path()) || it->path().extension() != ".as")
        {
            if (fs::is_directory(it->path()))
                create_directory(compute(local, protocol, it->path()));
            continue;
        }
        if (it->path().string().find("IItemCriterion") != std::string::npos)
            continue;
        T f { std::ifstream { it->path().string() } };
        f.parse();
        paths.emplace(f.class_name(),
                      compute(local, protocol, it->path().parent_path())
                      / (to_cpp_case(f.class_name()) + ".hpp"));
        files.emplace(f.class_name(), std::move(f));
    }
}


int main(int argc, const char ** argv)
{
    std::string path = "./protocol";
    if (argc > 1)
        path = argv[1];
    fs::path protocol;
    std::istringstream ss { path };
    ss >> protocol;
    
    if (!fs::is_directory(protocol))
        throw std::runtime_error { path + " is not a directory or doesn't exist" };

    auto local = fs::current_path() / "cpp" ;
    if (fs::exists(local) && fs::is_directory(local))
        fs::remove_all(local);
    fs::create_directory(local);
    fs::create_directory(local / "enums");
    fs::create_directory(local / "messages");
    fs::create_directory(local / "types");
    fs::create_directory(local / "datacenter");
    
    /* enums */
    std::cout << "Translating enums..." << std::endl;
    for (fs::recursive_directory_iterator it { protocol / "enums" };
         it != fs::recursive_directory_iterator { }; ++it)
    {
        if (!fs::is_regular_file(it->path()) || it->path().extension() != ".as")
        {
            if (fs::is_directory(it->path()))
                create_directory(compute(local, protocol, it->path()));
            continue;
        }
        enum_file f { std::ifstream { it->path().string() } };
        f.parse();
        make_cpp_file(f.cpp_output(),
                      compute(local, protocol, it->path().parent_path())
                      / (to_cpp_case(f.class_name()) + ".hpp"));
    }

    /* messages / types */
    std::cout << "Translating messages and types..." << std::endl;
    std::unordered_map<std::string, network_file> network;
    std::unordered_map<std::string, fs::path> paths;
    
    retrieve(network, paths, local, protocol, "messages");
    retrieve(network, paths, local, protocol, "types");

    for (auto && it : paths)
    {
        auto && f = network.at(it.first);
        make_cpp_file(f.cpp_output(network), it.second);
    }

    /* datacenter */
    std::cout << "Translating datacenter..." << std::endl;
    std::unordered_map<std::string, datacenter_file> datacenter;
    paths.clear();
    retrieve(datacenter, paths, local, protocol, "datacenter");
    for (auto && it : paths)
    {
        auto && f = datacenter.at(it.first);
        make_cpp_file(f.cpp_output(datacenter), it.second);
    }

    return 0;
}
