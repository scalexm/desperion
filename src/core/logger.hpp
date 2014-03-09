//
//  logger.hpp
//  core
//
//  Created by Alexandre Martin on 29/07/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#ifndef core_logger_hpp
#define core_logger_hpp

#include "singleton.hpp"
#include <string>
#include <fstream>
#include <ostream>
#include <unordered_map>
#include <list>

class logger : public singleton<logger>
{
    friend class singleton<logger>;
private:
    class log_folder
    {
    private:
        std::ofstream _file;
        std::string _prefix, _hour;

    public:
        explicit log_folder(std::string);
        log_folder & write_date();

        template<class T>
        std::ostream & operator <<(const T & t)
        { return (_file << t); }
    };

    std::string _prefix;
    std::unordered_map<std::string, log_folder> _folders;

public:
    explicit logger(std::string prefix = ".");
    void set_targets(const std::list<std::string> &);
    std::ostream & operator ()(const std::string &, const std::string &, int);
};

#define log_to(X) logger::instance()((X), __FILE__, __LINE__)

#endif
