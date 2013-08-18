//
//  session.cpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "common.hpp"
#include "session_impl.hpp"
#include "application.hpp"
#include "../core/sql_error.hpp"
#include "../core/logger.hpp"
#include "../core/protocol/dofus.hpp"
#include "../core/protocol/types/connection/game_server_informations.hpp"

void session::load_patch()
{
    session::impl::load_patch();
}

std::shared_ptr<session> session::create(boost::asio::ip::tcp::socket && socket)
{
    return std::shared_ptr<session> { new session { std::move(socket) } };
}

session::session(boost::asio::ip::tcp::socket && socket) : dofus_session { std::move(socket),
    std::bind(&session::handle_error, this) }, _impl { this }
{
}

session::~session()
{
    //  willingly empty
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

void session::handle_error()
{
    auto self = this->shared_from_this();
    application::instance().service().post([self]() { });
}

void session::handle_new_message(int16_t opcode, std::shared_ptr<byte_buffer> packet)
{
    application::instance().execute(&session::process_data, this->shared_from_this(), opcode,
                                    std::move(packet));
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

void session::process_data(int16_t opcode, std::shared_ptr<byte_buffer> & packet)
{
    try {
        _impl->process_data(opcode, *packet);
    } catch(const sql_error & e) {
        log_to("error") << "sql error: " << e.what() << "\n";
    } catch(const std::exception & e) {
        log_to("error") << e.what() << "\n";
    }
}
