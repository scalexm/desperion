//
//  game_server.hpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef login_server_game_server_hpp
#define login_server_game_server_hpp

#include <string>
#include <unordered_map>

class sql_field;
using field_map = std::unordered_map<std::string, sql_field>;

class game_server
{
private:
    int16_t _id;
    std::string _key;
    uint16_t _players_limit;
    uint8_t _min_level;
public:
    game_server(int16_t, const field_map &);
    int8_t get_state(uint8_t, bool) const;

    int16_t id() const
    { return _id; }

    uint8_t min_level() const
    { return _min_level; }

    uint16_t players_limit() const
    { return _players_limit; }

    const std::string & key() const
    { return _key; }
};

#endif
