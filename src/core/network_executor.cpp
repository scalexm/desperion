//
//  network_executor.cpp
//  core
//
//  Created by Alexandre Martin on 02/03/2014.
//  Copyright (c) 2014 alexm. All rights reserved.
//

#include "common.hpp"
#include "network_executor.hpp"
#include "byte_buffer.hpp"
#include "protocol/dofus.hpp"

void network_executor::close_socket()
{
    if (_socket.is_open())
    {
        boost::system::error_code ec;
        _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        _socket.close(ec);
    }
}

void network_executor::start_read(std::shared_ptr<abstract_session> owner)
{
    boost::asio::async_read(_socket,
                            boost::asio::buffer(&_header, sizeof(_header)),
                            _strand.wrap(std::bind(&network_executor::handle_read_header,
                                                   this,
                                                   std::placeholders::_1,
                                                   std::move(owner))));
}

void network_executor::handle_read_header(const boost::system::error_code & ec,
                                          std::shared_ptr<abstract_session> & owner)
{
    if (ec)
        return _handle_error(ec);

#ifdef BOOST_LITTLE_ENDIAN
    reverse_bytes((uint8_t *)&_header, sizeof(_header));
#endif
    _length.resize(_header & 3);

    boost::asio::async_read(_socket, boost::asio::buffer(_length),
                            _strand.wrap(std::bind(&network_executor::handle_read_length,
                                                   this,
                                                   std::placeholders::_1,
                                                   std::move(owner))));
}

void network_executor::handle_read_length(const boost::system::error_code & ec,
                                          std::shared_ptr<abstract_session> & owner)
{
    if (ec)
        return _handle_error(ec);

    size_t length = 0;
    for (size_t a = 0; a < _length.size(); ++a)
        length = (length << 8) + _length[a];
    _raw_data.resize(length);
    _length.clear();

    boost::asio::async_read(_socket, boost::asio::buffer(_raw_data),
                            _strand.wrap(std::bind(&network_executor::handle_read_raw_data,
                                                   this,
                                                   std::placeholders::_1,
                                                   std::move(owner))));
}

void network_executor::handle_read_raw_data(const boost::system::error_code & ec,
                                            std::shared_ptr<abstract_session> & owner)
{
    if (ec)
        return _handle_error(ec);

    _handle_message(_header >> 2, std::make_shared<byte_buffer>(_raw_data));
    _header = 0;
    _raw_data.clear();
    start_read(std::move(owner));
}

// std::shared_ptr<byte_buffer> must outlive write execution
void network_executor::handle_write(const boost::system::error_code & ec,
                                    std::shared_ptr<byte_buffer> &,
                                    std::shared_ptr<abstract_session> & owner, bool disconnect)
{
    if (ec)
        _handle_error(ec);
    else if (disconnect)
        close_socket();
}

network_executor::network_executor(boost::asio::ip::tcp::socket && socket,
                                   error_handler handle_error, message_handler handle_message
                                   )
    : _socket { std::move(socket) }, _strand { _socket.get_io_service() },
    _handle_error { std::move(handle_error) }, _handle_message { std::move(handle_message) }
{
}

network_executor::~network_executor()
{
    close_socket();
}

void network_executor::write(const byte_buffer & packet)
{
    if (!_packet)
        _packet = std::make_shared<byte_buffer>();
    *_packet << packet;
}

void network_executor::write(const protocol::dofus_unit & packet)
{
    if (!_packet)
        _packet = std::make_shared<byte_buffer>();
    protocol::fmt(*_packet, packet);
}

bool network_executor::flush(std::shared_ptr<abstract_session> owner, bool disconnect)
{
    if (!_packet || empty(*_packet))
        return false;
    boost::asio::async_write(_socket, boost::asio::buffer(data(*_packet), _packet->size()),
                             _strand.wrap(std::bind(&network_executor::handle_write,
                                                    this,
                                                    std::placeholders::_1,
                                                    std::move(_packet),
                                                    std::move(owner),
                                                    disconnect)));
    _packet.reset();
    return true;
}