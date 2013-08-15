//
//  game_session_impl.hpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef login_server_game_session_impl_hpp
#define login_server_game_session_impl_hpp

#include "game_session.hpp"
#include "../core/pimpl_impl.hpp"
#include <unordered_map>

class game_session::impl
{
private:
    struct packet_handler
    {
        void (game_session::impl::*handler)(byte_buffer &);
        req_flag flag;
    };

    static const std::unordered_map<int16_t, packet_handler> _handlers;
    game_session * _owner;
    const class game_server * _server = nullptr;
    int8_t _state = 3;
    std::string _salt, _alternative_ip;
    uint16_t _port, _players = 0;

    void handle_state_message(byte_buffer &);
    void handle_players_message(byte_buffer &);
    void handle_connect_message(byte_buffer &);
public:
    impl(game_session *);
    ~impl();
    void start();
    bool is_allowed(int16_t) const;
    void process_data(int16_t, byte_buffer &);
    void send_disconnect_player_message(int);

    const class game_server * game_server() const
    { return _server; }
    
    int8_t state() const
    { return _state; }
    
    const std::string & alternative_ip() const
    { return _alternative_ip; }
    
    uint16_t port() const
    { return _port; }
    
    uint16_t players() const
    {return _players; }
};

#endif
