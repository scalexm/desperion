//
//  abstract_session.hpp
//  core
//
//  Created by Alexandre Martin on 02/03/2014.
//  Copyright (c) 2014 alexm. All rights reserved.
//

#ifndef core_abstract_session_hpp
#define core_abstract_session_hpp

#include "network_executor.hpp"
#include <ctime>

class abstract_session : public std::enable_shared_from_this<abstract_session>
{
protected:
    network_executor _executor;
    time_t _start_time = time(nullptr);
    bool _going_to_disconnect = false;

    class flush_guard
    {
    private:
        abstract_session & _owner;;
        bool _disconnect;

    public:
        flush_guard(abstract_session &, bool);
        flush_guard(flush_guard &&) = default;
        ~flush_guard();
        
        void write(const byte_buffer &);
        void write(const protocol::dofus_unit &);
    };

public:
    abstract_session(boost::asio::ip::tcp::socket &&, network_executor::error_handler,
                     network_executor::message_handler);

    flush_guard make_guard(bool disconnect = false);
};

#endif
