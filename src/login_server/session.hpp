//
//  session.hpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#ifndef login_server_session_hpp
#define login_server_session_hpp

#include "../core/abstract_session.hpp"
#include "../core/pimpl.hpp"
#include <boost/asio.hpp>
#include <string>

class game_server;

namespace protocol
{
    class game_server_informations;
    class identification_message;
    using game_server_informations_ptr = std::unique_ptr<game_server_informations>;
}

class session : public abstract_session
{
private:
    class impl;
    pimpl<impl> _impl;

    session(boost::asio::ip::tcp::socket &&);

// --- unsafe, called in socket_listener threads
    void handle_error(const boost::system::error_code &);
    void handle_new_message(int16_t, std::shared_ptr<byte_buffer>);
// ---

    void handle_identification(const std::shared_ptr<protocol::identification_message> &);
    void finish_identification(int16_t, int16_t, bool);

    void process_data(int16_t, std::shared_ptr<byte_buffer> &);
public:
    struct account_data
    {
        std::string pseudo;
        int guid = -1;
        uint8_t level;
        std::string secret_question;
        std::string login;
    };

    static void load_patch();
    static std::shared_ptr<session> create(boost::asio::ip::tcp::socket &&);

    ~session();
    void start();
    bool can_select(int8_t) const;
    protocol::game_server_informations_ptr get_server_status(const game_server *) const;
    bool is_subscriber() const;
    const struct account_data & account_data() const;
    time_t subscription_end() const;
};

#endif
