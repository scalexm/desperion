//
//  abstract_application.hpp
//  core
//
//  Created by Alexandre Martin on 04/08/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#ifndef core_abstract_application_hpp
#define core_abstract_application_hpp

#include <condition_variable>
#include <chrono>
#include <boost/asio.hpp>

enum class shutdown_type
{
    NOT_REQUESTED,
    NORMAL,
    REBOOT,
};

class abstract_application
{
public:
    void shutdown(shutdown_type s);

    int64_t uptime() const
    { return (std::chrono::system_clock::now() - _start).count(); }

    shutdown_type get_shutdown() const
    { return _shutdown; }

    template<class... Args>
    void execute(Args && ... args) // less verbose than raw std::bind
    { _service.post(std::bind(std::forward<Args>(args)...)); }

    boost::asio::io_service & service()
    { return _service; }
    
protected:
    boost::asio::io_service _service;
    std::unique_ptr<boost::asio::io_service::work> _work;
    std::condition_variable _condition;

    abstract_application();

    void set_title(const std::string &);

private:
    volatile shutdown_type _shutdown = shutdown_type::NOT_REQUESTED;
    std::chrono::time_point<std::chrono::system_clock> _start = std::chrono::system_clock::now();
};

#endif
