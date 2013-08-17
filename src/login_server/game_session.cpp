//
//  game_session_impl.cpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
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

    struct hello_desperion_message : network::dofus_unit
    {
        int16_t id() const override
        { return network::opcode::SMSG_HELLO_DESPERION; }

        hello_desperion_message(const std::string & salt)
        {
            _data << salt;
        }
    };

    struct disconnect_player_message : network::dofus_unit
    {
        int16_t id() const override
        { return network::opcode::SMSG_DISCONNECT_PLAYER; }

        disconnect_player_message(const int & account)
        {
            _data << account;
        }
    };

    /* read */

    struct connect_message : network::dofus_unit
    {
        int16_t server_id;
        uint16_t port;
        std::string key;
        int8_t state;
        std::string alternative_ip;

        int16_t id() const override
        { return network::opcode::CMSG_CONNECT; }

        connect_message(byte_buffer & data)
        {
            data >> server_id >> port >> key >> state >> alternative_ip;
        }
    };

    struct state_message : network::dofus_unit
    {
        int8_t state;

        int16_t id() const override
        { return network::opcode::CMSG_STATE; }

        state_message(byte_buffer & data)
        {
            data >> state;
        }
    };

    struct players_message : network::dofus_unit
    {
        uint16_t players;

        int16_t id() const override
        { return network::opcode::CMSG_PLAYERS; }

        players_message(byte_buffer & data)
        {
            data >> players;
        }
    };
}

const std::unordered_map<int16_t, game_session::packet_handler> game_session::_handlers
{
    { network::opcode::CMSG_CONNECT, { &game_session::handle_connect_message,
        req_flag::NOT_CONNECTED } },
    { network::opcode::CMSG_STATE, { &game_session::handle_state_message,
        req_flag::CONNECTED } },
    { network::opcode::CMSG_PLAYERS, { &game_session::handle_players_message,
        req_flag::CONNECTED } }
};

std::shared_ptr<game_session> game_session::create(boost::asio::io_service & ios,
                                                   boost::asio::io_service & ws)
{
    return std::shared_ptr<game_session> { new game_session { ios, ws } };
}

game_session::game_session(boost::asio::io_service & ios, boost::asio::io_service & ws)
    : abstract_session { ios, ws }
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

void game_session::send(const network::dofus_unit & packet, bool disconnect)
{
    _executor.send(packet, this->shared_from_this(), disconnect);
}

void game_session::write(const network::dofus_unit & packet)
{
    _executor.write(packet);
}

void game_session::flush(bool disconnect)
{
    _executor.flush(this->shared_from_this(), disconnect);
}


void game_session::start()
{
    _salt = random_string(30);
    send(hello_desperion_message { _salt });
    _executor.start_read(this->shared_from_this());
}

void game_session::process_data(const network_message & message)
{
    auto it = _handlers.find(message.opcode);
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
    (this->*it->second.handler)(*message.packet);
}

void game_session::send_disconnect_player_message(int id)
{
    send(disconnect_player_message { id });
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
    if (gs == nullptr)
    {
        log_to("info") << "unknown server tried to log with game server id "
            << data.server_id << "\n";
        return send(network::basic_no_operation_message { }, true);
    }
    else if (utils::compute_md5_digest(_salt + utils::compute_md5_digest(gs->key()))
             != data.key)
    {
        log_to("info") << "[WARNING] server " << data.server_id
            << " tried to connect with wrong key, remote addr: "
            << get_address().to_string() << "\n";
        return send(network::basic_no_operation_message { }, true);
    }
    else if (g_world.get_game_session(data.server_id) != nullptr)
    {
        log_to("info") << "[WARNING] server " << data.server_id
            << " tried to connect but was already connected\n";
        return send(network::basic_no_operation_message { }, true);
    }
    _state = data.state;
    _port = data.port;
    _alternative_ip = data.alternative_ip;
    _server = gs;
    g_world.add_game_session(this);
    g_world.refresh_game_server(_server);
}
