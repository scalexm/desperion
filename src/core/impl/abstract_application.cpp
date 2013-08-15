//
//  abstract_application.cpp
//  core
//
//  Created by Alexandre Martin on 04/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "../common.hpp"
#include "../abstract_application.hpp"
#ifdef _WIN32
#include <cstdlib>
#else
#include <iostream>
#endif

abstract_application::abstract_application()
    : _work { std::make_unique<boost::asio::io_service::work>(_service) }
{
    
}

void abstract_application::shutdown(shutdown_type s)
{
    _shutdown = s;
    _work.reset();
    _condition.notify_all();
}

void abstract_application::set_title(const std::string & title)
{
#ifdef _WIN32
    auto cmd = "TITLE " + title;
    system(cmd.c_str());
#else
    std::cout << "\033]0;" << title << "\007";
#endif
}
