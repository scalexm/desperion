//
//  application.hpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef login_server_application_hpp
#define login_server_application_hpp

#include "../core/abstract_application.hpp"
#include "../core/singleton.hpp"
#include "../core/pimpl.hpp"

class sql_database;
class xml_configuration;
class world;

class application : public abstract_application, public singleton<application>
{
    friend class singleton<application>;
private:
    class impl;
    pimpl<impl> _impl;

    application();
    
public:
    ~application();

    shutdown_type run(int, const char **) override;
    sql_database & database();
    xml_configuration & config();
    class world & world();
};

#define g_database application::instance().database()
#define g_config application::instance().config()
#define g_world application::instance().world()

#endif
