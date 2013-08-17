//
//  world.cpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "common.hpp"
#include "world_impl.hpp"
#include "../core/protocol/dofus.hpp"
#include "../core/protocol/types/connection/game_server_informations.hpp"

world::world()
{
    // willingly empty
}

world::~world()
{
    // willingly empty
}

void world::init()
{
    _impl->init();
}

void world::add_session(session * s)
{
    _impl->add_session(s);
}

void world::delete_session(int id)
{
    _impl->delete_session(id);
}

session * world::get_session(int id) const
{
    return _impl->get_session(id);
}

session * world::get_session(const std::string & pseudo) const
{
    return _impl->get_session(pseudo);
}

void world::add_game_session(game_session * s)
{
    _impl->add_game_session(s);
}

void world::delete_game_session(int id)
{
    _impl->delete_game_session(id);
}

game_session * world::get_game_session(int id) const
{
    return _impl->get_game_session(id);
}

const game_server * world::get_game_server(int16_t id) const
{
    return _impl->get_game_server(id);
}

void world::refresh_game_server(const game_server * gs)
{
    _impl->refresh_game_server(gs);
}

std::vector<network::game_server_informations_ptr> world::get_server_informations(session * s) const
{
    return _impl->get_server_informations(s);
}

uint16_t world::get_players() const
{
    return _impl->get_players();
}

uint16_t world::get_max_players() const
{
    return _impl->get_max_players();
}