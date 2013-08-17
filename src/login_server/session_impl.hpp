//
//  session_impl.hpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef login_server_session_impl_hpp
#define login_server_session_impl_hpp

#include "session.hpp"
#include "../core/pimpl_impl.hpp"
#include "../core/auth_queue.hpp"
#include <unordered_map>

class session::impl
{
private:
    enum class req_flag
    {
        NOT_CONNECTED,
        CONNECTED,
        OUT_OF_QUEUE,
    };

    struct packet_handler
    {
        void (session::impl::*handler)(byte_buffer &);
        req_flag flag;
    };

    const static std::unordered_map<int16_t, packet_handler> _handlers;
    static auth_queue<session, network::identification_message> _queue;
    static std::vector<int8_t> _raw_data_patch;

    session * _owner;
    time_t _subscription_end;
    boost::asio::deadline_timer _idle_timer, _queue_timer;
    struct account_data _account_data;
    size_t _queue_counter = 0, _queue_size = 0;

    struct count
    { uint8_t count = 0; };

    std::unordered_map<int16_t, count> _counts;

    void handle_identification_message(byte_buffer &);
    void handle_server_selection_message(byte_buffer &);
    bool handle_server_selection(const game_server *, bool);
    void handle_acquaintance_search_message(byte_buffer &);

    void send_servers_list();
    void update_idle_timer();
    void idle_callback(const boost::system::error_code &);
    void queue_callback(const boost::system::error_code &);

public:
    static void load_patch();
    impl(session *);
    ~impl();
    void start();
    void process_data(const dofus_executor::message & message);
    bool can_select(int8_t) const;
    network::game_server_informations_ptr get_server_status(const game_server *) const;
    void handle_identification(const std::shared_ptr<network::identification_message> &);
    void finish_identification(int16_t, int16_t, bool);

    void send(const network::dofus_unit &, bool disconnect = false);
    void write(const network::dofus_unit &);
    void flush(bool disconnect = false);

    bool is_subscriber() const
    { return _subscription_end > time(nullptr); }

    const struct account_data & account_data() const
    { return _account_data; }

    time_t subscription_end() const
    { return _subscription_end; }
};

#endif
