//
//  session.hpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef login_server_session_hpp
#define login_server_session_hpp

#include "../core/protocol/dofus_executor.hpp"
#include "../core/pimpl.hpp"
#include <boost/asio.hpp>
#include <string>

class game_server;
namespace network
{
    class game_server_informations;
    class identification_message;
    using game_server_informations_ptr = std::unique_ptr<game_server_informations>;
}

class session : public dofus_session, public std::enable_shared_from_this<session>
{
private:
    class impl;
    pimpl<impl> _impl;

    session(boost::asio::ip::tcp::socket &&);

// --- unsafe, called in socket_listener threads
    void handle_error();
    void handle_new_message(int16_t, std::shared_ptr<byte_buffer>) override;
// ---

    void handle_identification(const std::shared_ptr<network::identification_message> &);
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
    void start() override;
    bool can_select(int8_t) const;
    network::game_server_informations_ptr get_server_status(const game_server *) const;
    bool is_subscriber() const;
    const struct account_data & account_data() const;
    time_t subscription_end() const;

    void send(const network::dofus_unit &, bool disconnect = false);
    void write(const network::dofus_unit &);
    void flush(bool disconnect = false);
};

#endif
