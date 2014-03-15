//
//  abstract_session.cpp
//  core
//
//  Created by Alexandre Martin on 02/03/2014.
//  Copyright (c) 2014 alexm. All rights reserved.
//

#include "common.hpp"
#include "abstract_session.hpp"

abstract_session::flush_guard::flush_guard(abstract_session & owner, bool disconnect)
    : _owner(owner), _disconnect { disconnect }
{
}

void abstract_session::flush_guard::write(const byte_buffer & packet)
{
    _owner._executor.write(packet);
}

void abstract_session::flush_guard::write(const protocol::dofus_unit & packet)
{
    _owner._executor.write(packet);
}

abstract_session::flush_guard::~flush_guard()
{
    if (_owner._executor.flush(_owner.shared_from_this(), _disconnect))
        _owner._going_to_disconnect = _disconnect;
}

abstract_session::abstract_session(boost::asio::ip::tcp::socket && socket,
                                   network_executor::error_handler handle_error,
                                   network_executor::message_handler handle_message)
    : _executor { std::move(socket), std::move(handle_error), std::move(handle_message) }
{

}

auto abstract_session::make_guard(bool disconnect) -> flush_guard
{
    return flush_guard { *this, disconnect };
}