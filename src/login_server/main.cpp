//
//  main.cpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "common.hpp"
#include "../core/logger.hpp"
#include "../core/utils.hpp"
#ifndef DEBUG
#include "../core/statistics_center.hpp"
#endif
#include "application.hpp"

int main(int argc, const char ** argv)
{
    std::cout << "starting desperion" << std::endl;
    logger::create();
#ifndef DEBUG
    statistics_center::create(LOGIN_VERSION_MAJOR, LOGIN_VERSION_MINOR, LOGIN_VERSION_RELEASE);
#endif
    try {
        while (application::create().run(argc, argv) == shutdown_type::REBOOT)
            application::kill();
    } catch (const std::exception & e) {
        utils::color<utils::TRED>(std::cout) << "an error occured, please see log files"
            << utils::cendl;
        log_to("error") << "unhandled exception: " << e.what() << "\n";
    }
    return 0;
}

