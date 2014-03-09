//
//  application.cpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#include "common.hpp"
#include "application_impl.hpp"

application::application() : _impl { this }
{
}

application::~application()
{
    //  willingly empty
}

shutdown_type application::run(int argc, const char ** argv)
{
    return _impl->run(argc, argv);
}

sql_database & application::database()
{
    return _impl->database();
}

xml_configuration & application::config()
{
    return _impl->config();
}

class world & application::world()
{
    return _impl->world();
}