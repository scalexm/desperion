//
//  world.hpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef login_server_world_hpp
#define login_server_world_hpp

#include "../core/singleton.hpp"
#include "../core/pimpl.hpp"
#include <vector>

class session;
class game_session;
class game_server;

namespace network
{
    class game_server_informations;
    using game_server_informations_ptr = std::unique_ptr<game_server_informations>;
}

class world : public singleton<world>
{
    friend class singleton<world>;
private:
    class impl;
    pimpl<impl> _impl;

    world();

public:
    ~world();
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

    uint16_t get_players() const;
    uint16_t get_max_players() const;
};

#endif
