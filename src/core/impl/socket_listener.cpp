//
//  socket_listener.cpp
//  core
//
//  Created by Alexandre Martin on 08/08/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#include "../common.hpp"
#include "../socket_listener.hpp"
#include "../run_service.hpp"


socket_listener::session_handler::session_handler(boost::asio::io_service & ios, uint16_t port)
    : _acceptor { ios }, _current_socket { ios }
{
    boost::asio::ip::tcp::endpoint ep { boost::asio::ip::tcp::v6(), port };
    _acceptor.open(ep.protocol());
    _acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    _acceptor.bind(ep);
    _acceptor.listen();

}

socket_listener::socket_listener()
    : _work { std::make_unique<boost::asio::io_service::work>(_service) }
{
}

socket_listener::~socket_listener()
{
    stop();
}

void socket_listener::spawn_threads(size_t threads)
{
    for (auto a = 1; a < threads; ++a)
        _threads.emplace_back(std::bind(run_service, std::ref(_service)));
}

void socket_listener::stop()
{
    _work.reset();
    _service.stop();
    _handlers.clear();
    for (auto && t : _threads)
        t.join();
    _threads.clear();
}