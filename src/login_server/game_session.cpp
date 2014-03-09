//
//  game_session_impl.cpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#include "common.hpp"
#include "game_session.hpp"
#include "world.hpp"
#include "game_server.hpp"
#include "application.hpp"
#include "../core/protocol/dofus.hpp"
#include "../core/utils.hpp"
#include "../core/logger.hpp"
#include "../core/protocol/identifiers.hpp"
#include "../core/protocol/messages/game/basic/basic_no_operation_message.hpp"
#include <random>

extern std::mt19937 _rng;

std::string random_string(size_t size)
{
    static const std::string alpha = "abcdefghijklmnopqrstuvwxyz1234567890-_?!/\\.,%$";
    std::string result;
    for(size_t a = 0; a < size; ++a)
        result += alpha[std::uniform_int_distribution<>(0, alpha.size() - 1)(_rng)];
    return result;
}

namespace
{
    /* write */

    struct hello_desperion_message : protocol::dofus_unit
    {
        int16_t id() const override
        { return protocol::opcode::SMSG_HELLO_DESPERION; }

        hello_desperion_message(const std::string & salt)
        {
            _data << salt;
        }
    };

    struct disconnect_player_message : protocol::dofus_unit
    {
        int16_t id() const override
        { return protocol::opcode::SMSG_DISCONNECT_PLAYER; }

        disconnect_player_message(const int & account)
        {
            _data << account;
        }
    };

    /* read */

    struct connect_message : protocol::dofus_unit
    {
        int16_t server_id;
        uint16_t port;
        std::string key;
        int8_t state;
        std::string alternative_ip;

        int16_t id() const override
        { return protocol::opcode::CMSG_CONNECT; }

        connect_message(byte_buffer & data)
        {
            data >> server_id >> port >> key >> state >> alternative_ip;
        }
    };

    struct state_message : protocol::dofus_unit
    {
        int8_t state;

        int16_t id() const override
        { return protocol::opcode::CMSG_STATE; }

        state_message(byte_buffer & data)
        {
            data >> state;
        }
    };

    struct players_message : protocol::dofus_unit
    {
        uint16_t players;

        int16_t id() const override
        { return protocol::opcode::CMSG_PLAYERS; }

        players_message(byte_buffer & data)
        {
            data >> players;
        }
    };
}

const std::unordered_map<int16_t, game_session::packet_handler> game_session::_handlers
{
    { protocol::opcode::CMSG_CONNECT, { &game_session::handle_connect_message,
        req_flag::NOT_CONNECTED } },
    { protocol::opcode::CMSG_STATE, { &game_session::handle_state_message,
        req_flag::CONNECTED } },
    { protocol::opcode::CMSG_PLAYERS, { &game_session::handle_players_message,
        req_flag::CONNECTED } }
};

std::shared_ptr<game_session> game_session::create(boost::asio::ip::tcp::socket && socket)
{
    return std::shared_ptr<game_session> { new game_session { std::move(socket) } };
}

game_session::game_session(boost::asio::ip::tcp::socket && socket) : abstract_session
{
    std::move(socket),
    std::bind(&game_session::handle_error, this, std::placeholders::_1),
    std::bind(&game_session::handle_new_message, this, std::placeholders::_1, std::placeholders::_2)
}
{

}

game_session::~game_session()
{
    if (_server != nullptr)
    {
        g_world.delete_game_session(_server->id());
        g_world.refresh_game_server(_server);
    }
}

void game_session::start()
{
    _salt = random_string(30);
    make_guard().write(hello_desperion_message { _salt });
    _executor.start_read(this->shared_from_this());
}

void game_session::send_disconnect_player_message(int id)
{
    make_guard().write(disconnect_player_message { id });
}

void game_session::handle_error(const boost::system::error_code &)
{
    auto self = this->shared_from_this();
    application::instance().service().post([self]() { });
}

void game_session::handle_new_message(int16_t opcode, std::shared_ptr<byte_buffer> packet)
{
    application::instance().execute(&game_session::process_data,
                                    std::static_pointer_cast<game_session>(this->shared_from_this()),
                                    opcode,
                                    std::move(packet));
}

void game_session::handle_state_message(byte_buffer & packet)
{
    state_message data { packet };
    _state = data.state;
    g_world.refresh_game_server(_server);
}

void game_session::handle_players_message(byte_buffer & packet)
{
    players_message data { packet };
    _players = data.players;
    g_world.refresh_game_server(_server);
}

void game_session::handle_connect_message(byte_buffer & packet)
{
    connect_message data { packet };
    auto gs = g_world.get_game_server(data.server_id);
    auto guard = make_guard(true);
    if (gs == nullptr)
    {
        log_to("info") << "unknown server tried to log with game server id "
            << data.server_id << "\n";
        return guard.write(protocol::basic_no_operation_message { });
    }
    else if (utils::compute_md5_digest(_salt + utils::compute_md5_digest(gs->key()))
             != data.key)
    {
        log_to("info") << "[WARNING] server " << data.server_id
            << " tried to connect with wrong key, remote addr: "
            << get_address().to_string() << "\n";
        return guard.write(protocol::basic_no_operation_message { });
    }
    else if (g_world.get_game_session(data.server_id) != nullptr)
    {
        log_to("info") << "[WARNING] server " << data.server_id
            << " tried to connect but was already connected\n";
        return guard.write(protocol::basic_no_operation_message { });
    }
    
    _state = data.state;
    _port = data.port;
    _alternative_ip = data.alternative_ip;
    _server = gs;
    g_world.add_game_session(this);
    g_world.refresh_game_server(_server);
}

void game_session::process_data(int16_t opcode, std::shared_ptr<byte_buffer> & packet)
{
    auto it = _handlers.find(opcode);
    if (it == end(_handlers))
        return;
    switch (it->second.flag)
    {
        case req_flag::NOT_CONNECTED:
            if (_server == nullptr)
                return;
            break;
        case req_flag::CONNECTED:
            if (_server != nullptr)
                return;
            break;
    }
    (this->*it->second.handler)(*packet);
}
