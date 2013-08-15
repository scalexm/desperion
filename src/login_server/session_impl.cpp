//
//  session_impl.cpp
//  login_server
//
//  Created by Alexandre Martin on 07/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "common.hpp"
#include "session_impl.hpp"
#include "world.hpp"
#include "application.hpp"
#include "game_server.hpp"
#include "game_session.hpp"
#include <set>
#include "../core/sql_database.hpp"
#include "../core/network/dofus.hpp"
#include "../core/network/identifiers.hpp"
#include "../core/query_result.hpp"
#include "../core/logger.hpp"
#include "../core/xml_configuration.hpp"
#include "../core/network/types/version/version.hpp"
#include "../core/network/types/version/version_extended.hpp"
#include "../core/network/messages/server/basic/system_message_display_message.hpp"
#include "../core/network/messages/security/raw_data_message.hpp"
#include "../core/network/messages/handshake/protocol_required.hpp"
#include "../core/network/enums/server_status_enum.hpp"
#include "../core/network/types/connection/game_server_informations.hpp"
#include "../core/network/messages/connection/servers_list_message.hpp"
#include "../core/network/messages/queues/login_queue_status_message.hpp"
#include "../core/network/messages/connection/identification_message.hpp"
#include "../core/network/messages/connection/identification_failed_message.hpp"
#include "../core/network/messages/connection/identification_failed_for_bad_version_message.hpp"
#include "../core/network/messages/connection/identification_failed_banned_message.hpp"
#include "../core/network/messages/connection/identification_success_message.hpp"
#include "../core/network/enums/server_connection_error_enum.hpp"
#include "../core/network/enums/identification_failure_reason_enum.hpp"
#include "../core/network/messages/game/basic/basic_no_operation_message.hpp"
#include "../core/network/messages/connection/server_selection_message.hpp"
#include "../core/network/messages/connection/selected_server_refused_message.hpp"
#include "../core/network/messages/connection/selected_server_data_message.hpp"
#include "../core/network/messages/connection/search/acquaintance_search_message.hpp"
#include "../core/network/messages/connection/search/acquaintance_search_error_message.hpp"
#include "../core/network/messages/connection/search/acquaintance_server_list_message.hpp"
#include "../core/network/messages/connection/hello_connect_message.hpp"
#include "../core/scope_guard.hpp"
#include "config_defaults.hpp"
#include "../core/utils.hpp"
#include <ctime>
#include <fstream>

std::string random_string(size_t);

namespace
{
    bool verify_version(const network::version_extended_ptr & v)
    {
        return v->major == network::DOFUS_VERSION_MAJOR
            && v->minor == network::DOFUS_VERSION_MINOR
            && v->release == network::DOFUS_VERSION_RELEASE
            && v->revision == network::DOFUS_VERSION_REVISION
            && v->patch == network::DOFUS_VERSION_PATCH
            && v->build_type == network::DOFUS_VERSION_BUILD_TYPE;
    }

    bool is_ip_banned(const std::string & address)
    {
        auto qr = g_database.query({ sql_database::prepare("check_ban_ip", address) });
        if(!qr)
            return false;
        auto && fields = qr.fetch();
        auto ban_end = fields.at("ban_end").get<time_t>();
        if(ban_end < time(nullptr))
        {
            g_database.async_query([](result_ptr qr, const std::string & e)
            {
                if(!e.empty())
                    log_to("error") << "sql error: " << e << "\n";
            }, { sql_database::prepare("delete_ban_ip", address) });
            return false;
        }
        else
            return true;
    }
}

const std::unordered_map<int16_t, session::impl::packet_handler> session::impl::_handlers
{
    { network::opcode::CMSG_IDENTIFICATION , { &impl::handle_identification_message,
        req_flag::NOT_CONNECTED } },
    { network::opcode::CMSG_SERVER_SELECTION, { &impl::handle_server_selection_message,
        req_flag::OUT_OF_QUEUE } },
    { network::opcode::CMSG_ACQUAINTANCE_SEARCH, { &impl::handle_acquaintance_search_message,
        req_flag::OUT_OF_QUEUE } }
};

auth_queue<session, network::identification_message> session::impl::_queue
{
    &session::handle_identification
};

std::vector<int8_t> session::impl::_raw_data_patch;

void session::impl::load_patch()
{
    auto path = g_config.get_property("patch_path", PATCH_PATH_DEFAULT);
    std::ifstream patch { path };
    if (!patch)
    {
        utils::color<utils::TRED>(std::cout)
            << "[CRITICAL] can't load patch file, desperion can't continue" << utils::cendl;
        throw std::runtime_error { "can't load patch file: "_s + path };
    }
    patch.seekg(0, std::ifstream::end);
    size_t size = patch.tellg();
    if (size == 0)
    {
        utils::color<utils::TYELLOW>(std::cout)
            << "[WARNING] patch file empty, did you miss something?" << utils::cendl;
    }
    else
    {
        patch.seekg(0, std::ifstream::beg);
        _raw_data_patch.resize(size );
        patch.read((char *)&_raw_data_patch[0], size);
    }
    
}

session::impl::impl(session * owner) : _owner { owner },
    _idle_timer { application::instance().service() },
    _queue_timer { application::instance().service() }
{
}

session::impl::~impl()
{
    if (_account_data.guid != -1)
        world::instance().delete_session(_account_data.guid);
    _idle_timer.cancel();
    _queue_timer.cancel();
}

void session::impl::send(const network::dofus_unit & message, bool disconnect)
{
    _owner->send(message, disconnect);
}

void session::impl::write(const network::dofus_unit & message)
{
    _owner->write(message);
}

void session::impl::flush(bool disconnect)
{
    _owner->flush(disconnect);
}

void session::impl::start()
{
    update_idle_timer();
    write(network::protocol_required { network::PROTOCOL_REQUIRED_BUILD, network::PROTOCOL_BUILD });
    write(network::hello_connect_message { "", { } });
    write(network::raw_data_message(_raw_data_patch));
    flush();
    _owner->start_read();
}

bool session::impl::is_allowed(int16_t id) const
{
    auto it = _handlers.find(id);
    if (it == end(_handlers))
        return false;
    switch (it->second.flag)
    {
        case req_flag::NOT_CONNECTED:
            return _account_data.guid == -1 && _queue_size == 0;
        case req_flag::OUT_OF_QUEUE:
            return _account_data.guid != -1 && _queue_size == 0;
    }
    return false;
}

void session::impl::process_data(int16_t id, byte_buffer & packet)
{
    auto it = _handlers.find(id);
    if (it == end(_handlers))
        return;
    update_idle_timer();
    (this->*it->second.handler)(packet);
}

bool session::impl::can_select(int8_t state) const
{
    switch (state)
    {
        case network::OFFLINE:
        case network::STARTING:
        case network::STATUS_UNKNOWN:
        case network::SAVING:
        case network::STOPING:
        case network::NOJOIN:
            return false;
        case network::ONLINE:
            return true;
        case network::FULL:
            return is_subscriber();
    }
    return false;
}

network::game_server_informations_ptr session::impl::get_server_status(const game_server * gs) const
{
    auto state = gs->get_state(_account_data.level, is_subscriber());
    auto it = _counts.find(gs->id());
    auto characters_count = it == end(_counts) ? 0 : it->second.count;
    return std::make_unique<network::game_server_informations>(gs->id(), state, 0,
                                                               can_select(state),
                                                               characters_count,
                                                               0);
}

void session::impl::send_servers_list()
{
    auto infos = world::instance().get_server_informations(_owner);
    write(network::servers_list_message { infos });
    flush();
}

void session::impl::handle_identification_message(byte_buffer & packet)
{
    auto data = std::make_shared<network::identification_message>(packet);
    if (g_config.get_property("server_maintenance", SERVER_MAINTENANCE_DEFAULT))
        return send(network::identification_failed_message { network::IN_MAINTENANCE }, true);
    else if (!verify_version(data->version))
    {
        auto version = std::make_unique<network::version>(network::DOFUS_VERSION_MAJOR,
                                                          network::DOFUS_VERSION_MINOR,
                                                          network::DOFUS_VERSION_RELEASE,
                                                          network::DOFUS_VERSION_REVISION,
                                                          network::DOFUS_VERSION_PATCH,
                                                          network::DOFUS_VERSION_BUILD_TYPE);
        return send(network::identification_failed_for_bad_version_message { network::BAD_VERSION,
            std::move(version) }, true);
    }
    std::weak_ptr<session> ptr { std::static_pointer_cast<session>(_owner->shared_from_this()) };
    auto result = _queue.push({ std::move(ptr), std::move(data) },
                              application::instance().service());
    _queue_size = result.first, _queue_counter = result.second;
    if (_queue_size > 1)
        queue_callback({ });
}

void session::impl::handle_identification(const std::shared_ptr<network::identification_message>
                                          & data)
{
    auto guard = make_guard([this]()
    {
        application::instance().execute(&auth_queue<session, network::identification_message>::next,
                                        std::ref(_queue));
    });
    
    if (is_ip_banned(_owner->_socket.remote_endpoint().address().to_string()))
        return send(network::identification_failed_message { network::WRONG_CREDENTIALS }, true);
    
    byte_buffer credentials { data->credentials };
    std::string login, password;
    credentials >> login >> password;
    auto qr = g_database.query({ sql_database::prepare("load_account", login) });
    if (!qr)
        return send(network::identification_failed_message { network::WRONG_CREDENTIALS }, true);
    
    auto && fields = qr.fetch();
    auto salt = fields.at("salt").get<std::string>();
    if (fields.at("password").get<std::string>() !=
        utils::compute_md5_digest(utils::compute_md5_digest(password) + salt))
        return send(network::identification_failed_message { network::WRONG_CREDENTIALS }, true);

    auto guid = fields.at("guid").get<int>();
    auto ban_end = fields.at("ban_end").get<time_t>();
    if (ban_end > 0)
    {
        if (ban_end < time(nullptr))
            g_database.query({ sql_database::prepare("update_ban", guid) });
        else
            return send(network::identification_failed_banned_message { network::BANNED, ban_end });
    }

    _subscription_end = fields.at("subscription_end").get<time_t>();
    _account_data.guid = guid;
    _account_data.pseudo = fields.at("pseudo").get<std::string>();
    _account_data.level = fields.at("level").get<uint8_t>();
    _account_data.secret_question = fields.at("secret_question").get<std::string>();
    _account_data.login = login;

    auto logged = fields.at("logged").get<int16_t>();
    auto last_server = fields.at("last_server").get<int16_t>();

    qr = g_database.query({ sql_database::prepare("character_counts", guid) });
    if (qr)
    {
        do
        {
            ++_counts[qr.fetch().at("server_id").get<int16_t>()].count;
        } while (qr.next_row());
    }
    
    application::instance().execute(&session::finish_identification,
                                    std::static_pointer_cast<session>(_owner->shared_from_this()),
                                    logged, last_server, data->autoconnect);
}

void session::impl::finish_identification(int16_t logged, int16_t last_server, bool auto_connect)
{
    auto s = world::instance().get_session(_account_data.guid);
    auto already_connected = false;
    if (s != nullptr)
    {
        already_connected = true;
        // if we don't set guid to -1, s deletion will call world::delete_session(guid)
        s->_impl->_account_data.guid = -1;
        s->send(network::basic_no_operation_message { }, true);
    }
    else if (world::instance().get_game_server(logged) != nullptr)
    {
        auto gs = world::instance().get_game_session(logged);
        if (gs != nullptr)
            gs->send_disconnect_player_message(_account_data.guid);
        else
        {
            return send(network::identification_failed_message { network::UNKNOWN_AUTH_ERROR },
                        true);
        }
        already_connected = true;
        world::instance().add_session(_owner);
    }
    else
        world::instance().add_session(_owner);
    write(network::identification_success_message { _account_data.level > 0, already_connected,
        _account_data.login, _account_data.pseudo, _account_data.guid, 0,
        _account_data.secret_question, _subscription_end, 0 });
    _queue_counter = _queue_size = 0;
    _queue_timer.cancel();

    if (auto_connect)
        if (handle_server_selection(world::instance().get_game_server(last_server), true))
            return;
    send_servers_list();
}

void session::impl::handle_server_selection_message(byte_buffer & packet)
{
    network::server_selection_message data { packet };
    handle_server_selection(world::instance().get_game_server(data.server_id), false);
}

bool session::impl::handle_server_selection(const game_server * gs, bool quiet)
{
    if (gs == nullptr)
        return false;
    
    auto state = gs->get_state(_account_data.level, is_subscriber());
    if (!can_select(state))
    {
        int8_t reason = network::SERVER_CONNECTION_ERROR_DUE_TO_STATUS;
        switch (state)
        {
            case network::FULL:
                reason = network::SERVER_CONNECTION_ERROR_SUBSCRIBERS_ONLY;
                break;
            case network::STATUS_UNKNOWN:
                reason = network::SERVER_CONNECTION_ERROR_NO_REASON;
                break;
        }
        if (!quiet)
            write(network::selected_server_refused_message { gs->id(), reason, state });
        return false;
    }

    auto ticket = random_string(30);
    auto self = _owner->shared_from_this();
    _owner->_going_to_disconnect = true;
    g_database.async_query([ticket, self, this, gs, quiet, state](result_ptr & qr,
                                                                  const std::string & e)
    {
        auto session = world::instance().get_game_session(gs->id());
        bool sql_error = !e.empty();
        if (sql_error || session == nullptr) // very bad luck to get second condition true
        {
            if (sql_error)
                log_to("error") << "sql error: " << e << "\n";
            _owner->_going_to_disconnect = false;
            if (!quiet)
            {
                send(network::selected_server_refused_message { gs->id(),
                    network::SERVER_CONNECTION_ERROR_NO_REASON, state });
            }
            else
                send_servers_list();
        }
        else
        {
            std::string ip;
            auto address = session->get_address();
            auto loopback = address.is_loopback()
                && _owner->_socket.remote_endpoint().address().is_loopback();
            send(network::selected_server_data_message { gs->id(),
                loopback ? session->alternative_ip() : address.to_string(),
                session->port(), true, ticket }, true);
                
        }
    }, { sql_database::prepare("update_ticket", ticket, _account_data.guid) });
    return true;
}

void session::impl::handle_acquaintance_search_message(byte_buffer & packet)
{
    network::acquaintance_search_message data { packet };
    auto self = _owner->shared_from_this();
    auto lower_nickname = boost::algorithm::to_lower_copy(data.nickname);
    g_database.async_query([self, this](result_ptr & qr, const std::string & e)
    {
        if (!e.empty())
        {
            log_to("error") << "sql error: " << e << "\n";
            send(network::acquaintance_search_error_message { 1 });
        }
        else if (!*qr)
            send(network::acquaintance_search_error_message { 2 });
        else
        {
            std::set<int16_t> results;
            
            do
            {
                auto && fields = qr->fetch();
                results.insert(fields.at("server_id").get<int16_t>());
            } while (qr->next_row());
            send(network::acquaintance_server_list_message(results));
        }
    }, { sql_database::prepare("acquaintance_search", lower_nickname) });
}

void session::impl::update_idle_timer()
{
    // we bind "this" to async_wait and not shared_from_this because this doesn't need to outlive idle_callback
    if (_idle_timer.expires_from_now(boost::posix_time::minutes {
        g_config.get_property("max_idle_time", MAX_IDLE_TIME_DEFAULT) }) > 0)
        _idle_timer.async_wait(std::bind(&impl::idle_callback, this, std::placeholders::_1));
}

void session::impl::idle_callback(const boost::system::error_code & ec)
{
    if (ec)
        return;
    _owner->send(network::system_message_display_message { true, 1, { } }, true);
}

void session::impl::queue_callback(const boost::system::error_code & ec)
{
    if (ec)
        return;
    // same thing here for async_wait
    _queue_timer.expires_from_now(boost::posix_time::seconds{ 2 });
    _queue_timer.async_wait(std::bind(&impl::queue_callback, this,
                                       std::placeholders::_1));
}
