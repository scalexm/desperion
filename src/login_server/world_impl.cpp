//
//  world_impl.cpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#include "common.hpp"
#include "world_impl.hpp"
#include "../core/protocol/dofus.hpp"
#include "../core/utils.hpp"
#include "../core/sql_database.hpp"
#include "../core/query_result.hpp"
#include "application.hpp"
#include "session.hpp"
#include "game_session.hpp"
#include "../core/protocol/types/connection/game_server_informations.hpp"
#include "../core/protocol/messages/connection/server_status_update_message.hpp"
#include "../core/protocol/enums/server_status_enum.hpp"
#include <iostream>
#include <chrono>
#include <boost/algorithm/string.hpp>

void world::impl::init()
{
    utils::color<utils::TGREEN>(std::cout) << "loading world..." << utils::cendl;
    load_game_servers();
    utils::color<utils::TGREEN>(std::cout) << "world loaded!" << utils::cendl;
}

void world::impl::load_game_servers()
{
    auto time = std::chrono::system_clock::now();
    auto qr = g_database.query({ sql_database::prepare("load") });
    if (!qr)
        return;
    do
    {
        auto && fields = qr.fetch();
        auto id = fields.at("id").get<int16_t>();
        _game_servers.emplace(std::piecewise_construct,
                              std::forward_as_tuple(id),
                              std::forward_as_tuple(id, fields));
    } while (qr.next_row());
    std::cout << _game_servers.size() << " game server(s) loaded in "
        << (std::chrono::system_clock::now() - time).count() << " microseconds" << std::endl;
}

void world::impl::add_session(session * s)
{
    _sessions.emplace(s->account_data().guid, s);
}

void world::impl::delete_session(int id)
{
    auto it = _sessions.find(id);
    if (it != end(_sessions))
        _sessions.erase(it);
}

session * world::impl::get_session(int id) const
{
    auto it = _sessions.find(id);
    if (it != end(_sessions))
        return it->second;
    return nullptr;
}

session * world::impl::get_session(const std::string & pseudo) const
{
    auto lower = boost::algorithm::to_lower_copy(pseudo);
    for (auto && it : _sessions)
        if (boost::algorithm::to_lower_copy(it.second->account_data().pseudo) == lower)
            return it.second;
    return nullptr;
}

void world::impl::add_game_session(game_session * s)
{
    _game_sessions.emplace(s->game_server()->id(), s);
}

void world::impl::delete_game_session(int id)
{
    auto it = _game_sessions.find(id);
    if (it != end(_game_sessions))
        _game_sessions.erase(it);
}

game_session * world::impl::get_game_session(int id) const
{
    auto it = _game_sessions.find(id);
    if (it != end(_game_sessions))
        return it->second;
    return nullptr;
}

const game_server * world::impl::get_game_server(int16_t id) const
{
    auto it = _game_servers.find(id);
    if (it != end(_game_servers))
        return &it->second;
    return nullptr;
}

void world::impl::refresh_game_server(const game_server * gs)
{
    if (application::instance().get_shutdown() != shutdown_type::NOT_REQUESTED)
        return;
    for (auto && it : _sessions)
    {
        it.second->make_guard().write(protocol::server_status_update_message
        {
            it.second->get_server_status(gs)
        });
    }
}

std::vector<protocol::game_server_informations_ptr> world::impl::
    get_server_informations(session * s)const
{
    std::vector<protocol::game_server_informations_ptr> results;
    for (auto && it : _game_servers)
        if (it.second.get_state(s->account_data().level, false) != protocol::NOJOIN)
            results.push_back(s->get_server_status(&it.second));
    return results;
}