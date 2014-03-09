//
//  run_service.hpp
//  core
//
//  Created by Alexandre Martin on 04/08/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#ifndef core_run_service_hpp
#define core_run_service_hpp

#include "sql_error.hpp"
#include <iostream>
#include <boost/asio.hpp>

// helper function to run worker thread
inline void run_service(boost::asio::io_service & ios)
{
    while (true)
    {
        try {
            ios.run();
            break;
        } catch(const sql_error & e) {
            std::cerr << "unhandled sql error: " << e.what() << std::endl;
        } catch (const std::exception & e) {
            std::cerr << "unhandled exception: " << e.what() << std::endl;
        }
    }
}

#endif
