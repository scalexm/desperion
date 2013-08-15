//
//  game_server.cpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "common.hpp"
#include "game_server.hpp"
#include "../core/sql_field.hpp"
#include "../core/network/enums/server_status_enum.hpp"
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
    auto s = world::instance().get_game_session(_id);
    if(level < _min_level)
        return network::server_status::NOJOIN;
    else if(s == nullptr)
        return network::server_status::OFFLINE;
    else if(s->state() == network::server_status::ONLINE && s->players() >= _players_limit
            && !subscriber)
        return network::server_status::FULL;
    return s->state();
}

