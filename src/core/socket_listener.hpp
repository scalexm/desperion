//
//  socket_listener.hpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#ifndef core_socket_listener_hpp
#define core_socket_listener_hpp

#include "non_movable.hpp"
#include <boost/asio.hpp>
#include <functional>
#include <thread>
#include <unordered_map>
#include <list>

class socket_listener : non_movable
{
private:
    class session_handler : non_movable
    {
    private:
        boost::asio::ip::tcp::acceptor _acceptor;
        boost::asio::ip::tcp::socket _current_socket;

        template<class Session>
        void handle_accept(const boost::system::error_code & ec)
        {
            if (ec)
                return;
            _current_socket.set_option(boost::asio::ip::tcp::no_delay(true));
            Session::create(std::move(_current_socket))->start();
            listen<Session>();
        }
        
    public:
        session_handler(boost::asio::io_service &, uint16_t);

        template<class Session>
        void listen()
        {
            _acceptor.async_accept(_current_socket,
                                   std::bind(&session_handler::handle_accept<Session>,
                                             this,
                                             std::placeholders::_1));
        }
    };

    boost::asio::io_service _service;
    std::list<std::thread> _threads;
    std::unique_ptr<boost::asio::io_service::work> _work;
    std::unordered_map<uint16_t, session_handler> _handlers;
    
public:
    socket_listener();
    ~socket_listener();
    void spawn_threads(size_t);
    void stop();

    template<class Session>
    void listen(uint16_t port)
    {
        auto && handler = _handlers.emplace(std::piecewise_construct,
                                            std::forward_as_tuple(port),
                                            std::forward_as_tuple(std::ref(_service),
                                                                  port)).first->second;
        handler.listen<Session>();
    }
};
#endif
