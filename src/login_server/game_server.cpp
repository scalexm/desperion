//
//  game_server.cpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#include "common.hpp"
#include "game_server.hpp"
#include "application.hpp"
#include "../core/sql_field.hpp"
#include "../core/protocol/enums/server_status_enum.hpp"
#include "world.hpp"
#include "game_session.hpp"

game_server::game_server(int16_t id, const field_map & fields) : _id { id },
    _key { fields.at("key").get<std::string>() },
    _players_limit { fields.at("players_limit").get<uint16_t>() },
    _min_level { fields.at("min_level").get<uint8_t>() }
{
}

int8_t game_server::get_state(uint8_t level, bool subscriber) const
{
    auto s = g_world.get_game_session(_id);
    if(level < _min_level)
        return protocol::server_status::NOJOIN;
    else if(s == nullptr)
        return protocol::server_status::OFFLINE;
    else if(s->state() == protocol::server_status::ONLINE && s->players() >= _players_limit
            && !subscriber)
        return protocol::server_status::FULL;
    return s->state();
}

