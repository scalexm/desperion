//
//  world_impl.hpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef login_server_world_impl_hpp
#define login_server_world_impl_hpp

#include "world.hpp"
#include "../core/pimpl_impl.hpp"
#include "game_server.hpp"

class world::impl
{
private:
    std::unordered_map<int, session *> _sessions;
    std::unordered_map<int, game_session *> _game_sessions;
    std::unordered_map<int16_t, game_server> _game_servers;
    uint16_t _max_players;

    void load_game_servers();
public:
    void init();

    void add_session(session *);
    void delete_session(int);
    session * get_session(int) const;
    session * get_session(const std::string &) const;

    void add_game_session(game_session *);
    void delete_game_session(int);
    game_session * get_game_session(int) const;

    const game_server * get_game_server(int16_t) const;
    void refresh_game_server(const game_server *);
    std::vector<network::game_server_informations_ptr> get_server_informations(session *) const;

    uint16_t get_players() const
    { return _sessions.size(); }
    
    uint16_t get_max_players() const
    { return _max_players; }
};

#endif
