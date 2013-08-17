//
//  dofus_executor.cpp
//  core
//
//  Created by Alexandre Martin on 17/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#include "../common.hpp"
#include "dofus_executor.hpp"
#include "dofus.hpp"
#include <iostream>

namespace
{
    void hex_dump(const byte_buffer & buffer)
    {
        std::cout << std::hex;
        auto data = ::data(buffer);
        for (size_t a = 0; a < buffer.size(); ++a)
        {
            if (data[a] <= 0xf)
                std::cout << "0";
            std::cout << uint16_t { data[a] } << " ";
        }
        std::cout << std::dec << std::endl;
    }

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

void dofus_executor::start_read(std::shared_ptr<base_type> owner)
{
    boost::asio::async_read(owner->_socket,
                            boost::asio::buffer(&_header, sizeof(_header)),
                            owner->_strand.wrap(std::bind(&dofus_executor::handle_read_header,
                                                   this,
                                                   std::placeholders::_1,
                                                   std::move(owner))));
}

void dofus_executor::format(std::shared_ptr<byte_buffer> & buffer,
                              const network::dofus_unit & message)
{
    auto opcode = message.id();
    auto && src = message.buffer();
    pack_packet(opcode, *buffer, src.size());
    *buffer << src;
}

void dofus_executor::send(const std::shared_ptr<byte_buffer> & packet,
                          std::shared_ptr<base_type> owner, bool disconnect)
{
    if (disconnect)
        owner->_going_to_disconnect = true;
    boost::asio::async_write(owner->_socket, boost::asio::buffer(data(*packet), packet->size()),
                             owner->_strand.wrap(std::bind(&dofus_executor::handle_write,
                                                           this,
                                                           std::placeholders::_1,
                                                           std::move(packet),
                                                           std::move(owner),
                                                           disconnect)));
}

void dofus_executor::send(const network::dofus_unit & message,
                          std::shared_ptr<base_type> owner, bool disconnect)
{
    auto packet = std::make_shared<byte_buffer>();
    dofus_executor::format(packet, message);
    send(packet, std::move(owner), disconnect);
}

void dofus_executor::write(const network::dofus_unit & message)
{
    if (!_packet)
        _packet = std::make_shared<byte_buffer>();
    dofus_executor::format(_packet, message);
}

void dofus_executor::flush(std::shared_ptr<base_type> owner, bool disconnect)
{
    if (!_packet || empty(*_packet))
        return;
    send(_packet, std::move(owner), disconnect);
    _packet.reset();
}

/* handlers */

void dofus_executor::handle_read_header(const boost::system::error_code & ec,
                                        std::shared_ptr<base_type> & owner)
{
    if (ec)
        return owner->handle_error();

#ifdef BOOST_LITTLE_ENDIAN
        reverse_bytes((uint8_t *)&_header, sizeof(_header));
#endif
    _length.resize(_header & 3);

    boost::asio::async_read(owner->_socket, boost::asio::buffer(_length),
                            owner->_strand.wrap(std::bind(&dofus_executor::handle_read_length,
                                                          this,
                                                          std::placeholders::_1,
                                                          std::move(owner))));
}

void dofus_executor::handle_read_length(const boost::system::error_code & ec,
                                        std::shared_ptr<base_type> & owner)
{
    if (ec)
        return owner->handle_error();

    size_t length = 0;
    for (size_t a = 0; a < _length.size(); ++a)
        length = (length << 8) + _length[a];
    _raw_data.resize(length);
    _length.clear();

    boost::asio::async_read(owner->_socket, boost::asio::buffer(_raw_data),
                            owner->_strand.wrap(std::bind(&dofus_executor::handle_read_raw_data,
                                                          this,
                                                          std::placeholders::_1,
                                                          std::move(owner))));
}

void dofus_executor::handle_read_raw_data(const boost::system::error_code & ec,
                                          std::shared_ptr<base_type> & owner)
{
    if (ec)
        return owner->handle_error();

    network_message message;
    message.opcode = _header >> 2;
    message.packet = std::make_shared<byte_buffer>(_raw_data);
    owner->handle_new_message(message);

    _header = 0;
    _raw_data.clear();
    start_read(std::move(owner));
}

// std::shared_ptr<byte_buffer> must outlive write execution
void dofus_executor::handle_write(const boost::system::error_code & ec,
                                  std::shared_ptr<byte_buffer> &,
                                  std::shared_ptr<base_type> & owner, bool disconnect)
{
    if (ec)
        owner->handle_error();
    else if (disconnect)
        owner->close_socket();
}