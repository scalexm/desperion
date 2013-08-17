//
//  session.cpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "common.hpp"
#include "session_impl.hpp"
#include "../core/protocol/dofus.hpp"
#include "../core/protocol/types/connection/game_server_informations.hpp"
#include <iostream>

void session::load_patch()
{
    session::impl::load_patch();
}

std::shared_ptr<session> session::create(boost::asio::io_service & ios,
                                         boost::asio::io_service & ws)
{
    return std::shared_ptr<session> { new session { ios, ws } };
}

session::session(boost::asio::io_service & ios, boost::asio::io_service & ws)
    : abstract_session { ios, ws }, _impl { this }
{
}

void session::send(const network::dofus_unit & unit, bool disconnect)
{
    _impl->send(unit, disconnect);
}

void session::write(const network::dofus_unit & unit)
{
    _impl->write(unit);
}

void session::flush(bool disconnect)
{
    _impl->flush(disconnect);
}

session::~session()
{
    //  willingly empty
}

void session::process_data(const dofus_executor::message & message)
{
    _impl->process_data(message);
}

void session::start()
{
    _impl->start();
}

bool session::can_select(int8_t state) const
{
    return _impl->can_select(state);
}

bool session::is_subscriber() const
{
    return _impl->is_subscriber();
}

auto session::account_data() const -> const struct account_data &
{
    return _impl->account_data();
}

network::game_server_informations_ptr session::get_server_status(const game_server * gs) const
{
    return _impl->get_server_status(gs);
}

time_t session::subscription_end() const
{
    return _impl->subscription_end();
}

void session::handle_identification(const std::shared_ptr<network::identification_message> & data)
{
    try {
        _impl->handle_identification(data);
    } catch (const std::exception & e) {
        std::cerr << "unhandled exception in auth thread: " << e.what() << std::endl;
    }
}

void session::finish_identification(int16_t logged, int16_t last_server, bool auto_connect)
{
    _impl->finish_identification(logged, last_server, auto_connect);
}
