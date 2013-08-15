//
//  game_session.hpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef login_server_game_session_hpp
#define login_server_game_session_hpp

#include "../core/pimpl.hpp"
#include "../core/abstract_session.hpp"

class game_server;

class game_session : public abstract_session
{
private:
    class impl;
    pimpl<impl> _impl;

    game_session(boost::asio::io_service &, boost::asio::io_service &);
    bool is_allowed(int16_t) const override;
    void process_data(int16_t, byte_buffer &) override;

public:
    static std::shared_ptr<game_session> create(boost::asio::io_service &,
                                                boost::asio::io_service &);
    ~game_session();
    void start() override;
    void send_disconnect_player_message(int);

    const class game_server * game_server() const;
    int8_t state() const;
    const std::string & alternative_ip() const;
    uint16_t port() const;
    uint16_t players() const;
    
    boost::asio::ip::address get_address() const
    { return _socket.remote_endpoint().address(); }
    
};

#endif
