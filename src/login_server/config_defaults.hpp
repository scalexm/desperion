//
//  config_defaults.hpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#ifndef login_server_config_defaults_hpp
#define login_server_config_defaults_hpp

#include <thread>

const size_t POOL_THREADS_DEFAULT = std::thread::hardware_concurrency();

const std::string DATABASE_HOST_DEFAULT = "127.0.0.1";
const std::string DATABASE_NAME_DEFAULT = "desperion_login";
const std::string DATABASE_USER_DEFAULT = "postgres";
const std::string DATABASE_PASSWORD_DEFAULT = "postgres";
const uint16_t DATABASE_PORT_DEFAULT = 5432;

const uint16_t SERVER_PORT_DEFAULT = 443;
const uint16_t SYSTEM_PORT_DEFAULT = 444;
const bool LOG_INFO_DEFAULT = true;
const bool LOG_DEBUG_DEFAULT = false;
const bool LOG_ERROR_DEFAULT = true;
const std::string QUERIES_PATH_DEFAULT = "queries.xml";
const std::string PATCH_PATH_DEFAULT = "patch.swf";

const uint8_t MAX_IDLE_TIME_DEFAULT = 10;
const bool SERVER_MAINTENANCE_DEFAULT = false;

#endif
