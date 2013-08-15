//
//  game_session.cpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "common.hpp"
#include "game_session_impl.hpp"

std::shared_ptr<game_session> game_session::create(boost::asio::io_service & ios,
                                                          boost::asio::io_service & ws)
{
    return std::shared_ptr<game_session> { new game_session { ios, ws } };
}

game_session::game_session(boost::asio::io_service & ios, boost::asio::io_service & ws)
    : abstract_session { ios, ws }, _impl { this }
{
    
}

game_session::~game_session()
{
    //  willingly empty
}

bool game_session::is_allowed(int16_t opcode) const
{
    return _impl->is_allowed(opcode);
}

void game_session::process_data(int16_t opcode, byte_buffer & packet)
{
    _impl->process_data(opcode, packet);
}

void game_session::start()
{
    _impl->start();
}

void game_session::send_disconnect_player_message(int id)
{
    _impl->send_disconnect_player_message(id);
}

const class game_server * game_session::game_server() const
{
    return _impl->game_server();
}

int8_t game_session::state() const
{
    return _impl->state();
}

const std::string & game_session::alternative_ip() const
{
    return _impl->alternative_ip();
}

uint16_t game_session::port() const
{
    return _impl->port();
}

uint16_t game_session::players() const
{
    return _impl->players();
}
