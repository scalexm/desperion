//
//  application_impl.cpp
//  login_server
//
//  Created by Alexandre Martin on 08/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "common.hpp"
#include "../core/socket_listener.hpp"
#include "../core/logger.hpp"
#include "../core/network/dofus.hpp"
#include "../core/utils.hpp"
#include "../core/run_service.hpp"
#include "world.hpp"
#include "session.hpp"
#include "game_session.hpp"
#include "application_impl.hpp"
#include "config_defaults.hpp"
#include <random>
#include <ctime>
#include <mutex>

std::mt19937 _rng;

application::impl::impl(application * owner) : _owner { owner }, _db { 3, owner->_service },
    _config { { "server.xml", "misc.xml" } }
{
    _rng.seed(time(nullptr));
}

application::impl::~impl()
{
    utils::color<utils::TBLUE>(std::cout) << "shutting down..." << utils::cendl;
}

void application::impl::start_database()
{
    xml_configuration queries { { _config.get_property("queries_path", QUERIES_PATH_DEFAULT) } };

    utils::color<utils::TBLUE>(std::cout) << "connecting to the local database..." << std::endl;
    _db.init(_config.get_property("database_host", DATABASE_HOST_DEFAULT),
                  _config.get_property("database_port", DATABASE_PORT_DEFAULT),
                  _config.get_property("database_user", DATABASE_USER_DEFAULT),
                  _config.get_property("database_password", DATABASE_PASSWORD_DEFAULT),
                  _config.get_property("database_name", DATABASE_NAME_DEFAULT));
    std::cout << "connection successful!\n" << utils::cendl;
    
    _db.load_queries(queries.get_properties());
}

shutdown_type application::impl::run(int argc, const char ** argv)
{
    std::list<std::string> targets;
    if (_config.get_property("log_info", LOG_INFO_DEFAULT))
        targets.emplace_back("info");
    if (_config.get_property("log_debug", LOG_DEBUG_DEFAULT))
        targets.emplace_back("debug");
    if (_config.get_property("log_error", LOG_ERROR_DEFAULT))
        targets.emplace_back("error");
    logger::instance().set_targets(std::move(targets));

    std::ostringstream version;
    version << LOGIN_VERSION_MAJOR << "." << LOGIN_VERSION_MINOR
        << "." << LOGIN_VERSION_RELEASE;
    _owner->set_title("desperion login server v" + version.str());

    std::cout << "\n";
    utils::color<utils::TBLUE>(std::cout)
        << ",------,  ,-----. ,-----, ,------. ,-----. ,------.  ,------. ,------, ,,    ,,\n"
        << "| ,--,  ` | .---' |  ,--` | ,--, | | .---' | ,--, |  `--||--' | ,--, | ||\\   ||\n"
        << "| |  |  | | |--.  |  `--, | |  | | | |--.  | |  | |     ||    | |  | | || \\  ||\n"
        << "| |  |  | | |--'  `---, | | `--` | | |--'  | `--` ,     ||    | |  | | ||  \\ ||\n"
        << "| '--'  , | '---, ,---| | | ,----` | '---, | ,-\\  \\  .--||--, | '--' | ||   \\||\n"
        << "`------`  `-----' `-----` `-`      `-----' `-`  '--' `------` `------` ``    `'\n";
    utils::color<utils::TGREEN>(std::cout)
        << "Dofus v" << network::DOFUS_VERSION_MAJOR << "." << network::DOFUS_VERSION_MINOR << "."
        << network::DOFUS_VERSION_RELEASE << "." << network::DOFUS_VERSION_REVISION << "."
        << network::DOFUS_VERSION_PATCH << "/" << network::DOFUS_VERSION_BUILD_TYPE << ", protocol "
        << network::PROTOCOL_BUILD << "/" << network::PROTOCOL_REQUIRED_BUILD << "\n"

        << "login server v" << version.str() << ", build date: " << __DATE__
        << " " << __TIME__ << "\n" << utils::cendl;

    try {
        start_database();
    } catch (const sql_error & e) {
        utils::color<utils::TRED>(std::cout) << "an sql error occured, please see log files"
            << utils::cendl;
        log_to("error") << "sql error: " << e.what() << "\n";
        return shutdown_type::NORMAL;
    }

    world::create().init();
    session::load_patch();

    socket_listener listener;
    auto port = _config.get_property("server_port", SERVER_PORT_DEFAULT);
    listener.listen<session>(port, _owner->_service);

    port = _config.get_property("system_port", SERVER_PORT_DEFAULT);
    listener.listen<game_session>(port, _owner->_service);

    std::cout << "\nuptime " << _owner->uptime() << " microseconds" << std::endl;

    listener.spawn_threads(_config.get_property("pool_threads", POOL_THREADS_DEFAULT));
    std::thread t { std::bind(&run_service, std::ref(_owner->_service)) };
    std::mutex m;
    std::unique_lock<std::mutex> lock { m };
    while (_owner->get_shutdown() == shutdown_type::NOT_REQUESTED)
        _owner->_condition.wait(lock);
    listener.stop();
    t.join();

    return shutdown_type::NORMAL;
}

