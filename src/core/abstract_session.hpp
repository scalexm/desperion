//
//  abstract_session2.hpp
//  core
//
//  Created by Alexandre Martin on 17/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef core_abstract_session_hpp
#define core_abstract_session_hpp

#include <ctime>
#include <boost/asio.hpp>

template<class Executor>
class abstract_session : public std::enable_shared_from_this<abstract_session<Executor>>
{
    friend Executor;
private:
    boost::asio::io_service & _main_service;
    boost::asio::io_service::strand _strand;

    void close_socket()
    {
        if (_socket.is_open())
        {
            boost::system::error_code ec;
            _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
            _socket.close(ec);
        }
    }

    void handle_new_message(typename Executor::message message)
    {
        _main_service.post(std::bind(&abstract_session::process_data,
                                     this->shared_from_this(),
                                     std::move(message)));
    }

protected:
    bool _going_to_disconnect = false;
    time_t _start_time = time(nullptr);
    boost::asio::ip::tcp::socket _socket;
    Executor _executor;

    abstract_session(boost::asio::io_service & ios, boost::asio::io_service & ms)
        : _socket { ios }, _strand { ios }, _main_service (ms)
    {

    }

    virtual void handle_error()
    {
        auto self = this->shared_from_this();
        // so that the session is destroyed in main thread
        _main_service.post([self]() { });
    }

    virtual ~abstract_session()
    {
        close_socket();
    }

    virtual void process_data(const typename Executor::message &) = 0;

public:
    virtual void start() = 0;

    boost::asio::ip::tcp::socket & socket()
    { return _socket; }

    time_t start_time() const
    { return _start_time; }
};

#endif
