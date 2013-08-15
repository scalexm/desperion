//
//  socket_listener.hpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef core_socket_listener_hpp
#define core_socket_listener_hpp

#include "non_movable.hpp"
#include <boost/asio.hpp>
#include <functional>
#include <thread>
#include <unordered_map>

class socket_listener : non_movable
{
private:
    class session_handler : non_movable
    {
    private:
        boost::asio::io_service & _main_service;
        boost::asio::ip::tcp::acceptor _acceptor;

        template<class Session>
        void handle_accept(const boost::system::error_code & ec,
                           std::shared_ptr<Session> & session)
        {
            if (ec)
                return;
            session->socket().set_option(boost::asio::ip::tcp::no_delay(true));
            session->start();
            listen<Session>();
        }
        
    public:
        session_handler(boost::asio::io_service &, boost::asio::io_service &, uint16_t);

        template<class Session>
        void listen()
        {
            auto session = Session::create(_acceptor.get_io_service(), _main_service);
            _acceptor.async_accept(session->socket(),
                                   std::bind(&session_handler::handle_accept<Session>,
                                             this,
                                             std::placeholders::_1,
                                             session));
        }
    };

    boost::asio::io_service _service;
    std::unordered_map<uint16_t, session_handler> _handlers;
    
public:
    socket_listener() = default;
    void spawn_threads(size_t);
    void stop();

    template<class Session>
    void listen(uint16_t port, boost::asio::io_service & ws)
    {
        auto && handler = _handlers.emplace(std::piecewise_construct,
                                            std::forward_as_tuple(port),
                                            std::forward_as_tuple(std::ref(_service), std::ref(ws),
                                                                  port)).first->second;
        handler.listen<Session>();
    }

};
#endif
