//
//  game_session_impl.cpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "common.hpp"
#include "game_session_impl.hpp"
#include "world.hpp"
#include "game_server.hpp"
#include "../core/utils.hpp"
#include "../core/logger.hpp"
#include "../core/network/dofus.hpp"
#include "../core/network/identifiers.hpp"
#include "../core/network/messages/game/basic/basic_no_operation_message.hpp"
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

const std::unordered_map<int16_t, game_session::impl::packet_handler> game_session::impl::_handlers
{
    { network::opcode::CMSG_CONNECT, { &impl::handle_connect_message, req_flag::NOT_CONNECTED } },
    { network::opcode::CMSG_STATE, { &impl::handle_state_message } },
    { network::opcode::CMSG_PLAYERS, { &impl::handle_players_message } }
};

game_session::impl::impl(game_session * owner) : _owner { owner }
{

}

game_session::impl::~impl()
{
    if (_server != nullptr)
    {
        world::instance().delete_game_session(_server->id());
        world::instance().refresh_game_server(_server);
    }
}

void game_session::impl::start()
{
    _salt = random_string(30);
    _owner->send(hello_desperion_message { _salt });
    _owner->start_read();
}

bool game_session::impl::is_allowed(int16_t id) const
{
    auto it = _handlers.find(id);
    if (it == end(_handlers))
        return false;
    switch (it->second.flag)
    {
        case req_flag::NOT_CONNECTED:
            return _server == nullptr;
        case req_flag::CONNECTED:
            return _server != nullptr;
    }
    return false;
}

void game_session::impl::process_data(int16_t id, byte_buffer & packet)
{
    auto it = _handlers.find(id);
    if (it == end(_handlers))
        return;
    (this->*it->second.handler)(packet);
}

void game_session::impl::send_disconnect_player_message(int id)
{
    _owner->send(disconnect_player_message { id });
}

void game_session::impl::handle_state_message(byte_buffer & packet)
{
    state_message data { packet };
    _state = data.state;
    world::instance().refresh_game_server(_server);
}

void game_session::impl::handle_players_message(byte_buffer & packet)
{
    players_message data { packet };
    _players = data.players;
    world::instance().refresh_game_server(_server);
}

void game_session::impl::handle_connect_message(byte_buffer & packet)
{
    connect_message data { packet };
    auto gs = world::instance().get_game_server(data.server_id);
    if (gs == nullptr)
    {
        log_to("info") << "unknown server tried to log with game server id "
            << data.server_id << "\n";
        return _owner->send(network::basic_no_operation_message { }, true);
    }
    else if (utils::compute_md5_digest(_salt + utils::compute_md5_digest(gs->key()))
             != data.key)
    {
        log_to("info") << "[WARNING] server " << data.server_id
            << " tried to connect with wrong key, remote addr: "
            << _owner->get_address().to_string() << "\n";
        return _owner->send(network::basic_no_operation_message { }, true);
    }
    else if (world::instance().get_game_session(data.server_id) != nullptr)
    {
        log_to("info") << "[WARNING] server " << data.server_id
            << " tried to connect but was already connected\n";
        return _owner->send(network::basic_no_operation_message { }, true);
    }
    _state = data.state;
    _port = data.port;
    _alternative_ip = data.alternative_ip;
    _server = gs;
    world::instance().add_game_session(_owner);
    world::instance().refresh_game_server(_server);
}
