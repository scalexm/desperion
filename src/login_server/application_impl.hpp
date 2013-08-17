//
//  application_impl.hpp
//  login_server
//
//  Created by Alexandre Martin on 08/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef login_server_application_impl_hpp
#define login_server_application_impl_hpp

#include "application.hpp"
#include "../core/pimpl_impl.hpp"
#include "../core/sql_database.hpp"
#include "../core/xml_configuration.hpp"
#include "world.hpp"

class application::impl
{
private:
    sql_database _db;
    xml_configuration _config;
    class world _world;
    application * _owner;

public:
    impl(application *);
    ~impl();
    
    void start_database();
    shutdown_type run(int, const char **);

    sql_database & database()
    { return _db; }

    xml_configuration & config()
    { return _config; }

    class world & world()
    { return _world; }
};

#endif
