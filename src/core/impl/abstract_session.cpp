//
//  abstract_session.cpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "../common.hpp"
#include "../abstract_session.hpp"
#include "../logger.hpp"
#include "../network/dofus.hpp"
#include "../sql_error.hpp"
#include <iostream>

void hex_dump(const byte_buffer & buffer)
{
    std::cout << std::hex;
    auto data = buffer.data();
    for (size_t a = 0; a < buffer.size(); ++a)
    {
        if (data[a] <= 0xf)
            std::cout << "0";
        std::cout << uint16_t { data[a] } << " ";
    }
    std::cout << std::dec << std::endl;
}

namespace
{
    uint8_t compute_type_len(size_t size)
    {
        if (size > 0xffff)
            return 3;
        else if (size > 0xff)
            return 2;
        else if (size > 0)
            return 1;
        else
            return 0;
    }

    void pack_packet(int16_t opcode, byte_buffer & header, size_t size)
    {
        auto compute = compute_type_len(size);
        int16_t val = (opcode << 2) | compute;
        header << val;
        switch (compute)
        {
            case 1:
                header << static_cast<uint8_t>(size);
                break;
            case 2:
                header << static_cast<uint16_t>(size);
                break;
            case 3:
                header << static_cast<uint8_t>((size >> 0x10) & 0xff);
                header << static_cast<uint16_t>(size & 0xffff);
                break;
        }
    }
}

void abstract_session::format(std::shared_ptr<byte_buffer> & buffer,
                              const network::dofus_unit & message)
{
    auto opcode = message.id();
    auto && src = message.buffer();
    pack_packet(opcode, *buffer, src.size());
    *buffer << src;
}

abstract_session::abstract_session(boost::asio::io_service & ios, boost::asio::io_service & ms)
    : _socket { ios }, _strand { ios }, _main_service(ms)
{

}

abstract_session::~abstract_session()
{
    close_socket();
}

void abstract_session::start_read()
{
    boost::asio::async_read(_socket, boost::asio::buffer(_header),
                            _strand.wrap(std::bind(&abstract_session::handle_read_header,
                                                   this->shared_from_this(),
                                                   std::placeholders::_1)));
}

void abstract_session::handle_error()
{
    auto self = this->shared_from_this();
    // so that the session is destroyed in main thread
    _main_service.post([self]() { });
}

void abstract_session::close_socket()
{
    if (_socket.is_open())
    {
        boost::system::error_code ec;
        _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
        _socket.close(ec);
    }
}

void abstract_session::handle_read_header(const boost::system::error_code & ec)
{
    if (ec)
        return handle_error();

    int16_t header = *((int16_t *)&_header[0]);
    if (byte_buffer::ENDIANNESS == endianness::LITTLE)
        swap_bytes((uint8_t *)&header, sizeof(header));
    _opcode = header >> 2;
    size_t type_len = header & 3;
    _length.resize(type_len);

    boost::asio::async_read(_socket, boost::asio::buffer(_length),
                            _strand.wrap(std::bind(&abstract_session::handle_read_length,
                                                   this->shared_from_this(),
                                                   std::placeholders::_1)));
}

void abstract_session::handle_read_length(const boost::system::error_code & ec)
{
    if (ec)
        return handle_error();

    size_t length = 0;
    for (size_t a = 0; a < _length.size(); ++a)
        length = (length << 8) + _length[a];
    _raw_data.resize(length);
    _length.clear();

    boost::asio::async_read(_socket, boost::asio::buffer(_raw_data),
                            _strand.wrap(std::bind(&abstract_session::handle_read_raw_data,
                                                   this->shared_from_this(),
                                                   std::placeholders::_1)));
}

void abstract_session::handle_read_raw_data(const boost::system::error_code & ec)
{
    if (ec)
        return handle_error();

    auto received = std::make_shared<byte_buffer>();
    auto size = _raw_data.size();
    if (size > 0)
        received->write_bytes(&_raw_data[0], size);

    _main_service.post(std::bind(&abstract_session::handle_process_data,
                                 this->shared_from_this(),
                                 _opcode,
                                 std::move(received)));

    _opcode = 0;
    _raw_data.clear();
    start_read();
}

void abstract_session::handle_process_data(int16_t opcode, std::shared_ptr<byte_buffer> & buf)
{
    if (_going_to_disconnect || !is_allowed(opcode))
        return;

    try {
        process_data(opcode, *buf);
    } catch (const sql_error & e) {
        log_to("error") << "sql error: " << e.what() << "\n";
    } catch (const std::exception& e) {
        log_to("error") << e.what() << "\n";
    }
    flush();
}

// std::shared_ptr<byte_buffer> must outlive write execution
void abstract_session::handle_write(const boost::system::error_code& ec,
                                    std::shared_ptr<byte_buffer>&, bool disconnect)
{
    if (ec)
        handle_error();
    else if (disconnect)
        close_socket();
}

void abstract_session::send(const std::shared_ptr<byte_buffer> & packet, bool disconnect)
{
    //hex_dump(*packet);
    //std::cout << std::endl;
    if (disconnect)
        _going_to_disconnect = true;
    boost::asio::async_write(_socket, boost::asio::buffer(packet->data(), packet->size()),
                             _strand.wrap(std::bind(&abstract_session::handle_write,
                                                    this->shared_from_this(),
                                                    std::placeholders::_1,
                                                    std::move(packet),
                                                    disconnect)));
}

void abstract_session::send(const network::dofus_unit & message, bool disconnect)
{
    auto packet = std::make_shared<byte_buffer>();
    abstract_session::format(packet, message);
    send(packet, disconnect);
}

void abstract_session::write(const network::dofus_unit & message)
{
    if (!_packet)
        _packet = std::make_shared<byte_buffer>();
    abstract_session::format(_packet, message);
}

void abstract_session::flush(bool disconnect)
{
    if (!_packet || _packet->data() == nullptr)
        return;
    send(_packet, disconnect);
    _packet.reset();
}