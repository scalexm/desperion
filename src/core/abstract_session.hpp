//
//  abstract_session.hpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef core_abstract_session_hpp
#define core_abstract_session_hpp

#include "non_movable.hpp"
#include <array>
#include <boost/asio.hpp>
#include <vector>
#include <ctime>

class byte_buffer;
namespace network { class dofus_unit; }

enum class req_flag
{
    NOT_CONNECTED,
    CONNECTED,
    OUT_OF_QUEUE,
    CHARACTER,
    IN_FIGHT,
    HAS_PARTY,
};

class abstract_session : public std::enable_shared_from_this<abstract_session>, non_movable
{
protected:
    bool _going_to_disconnect = false;
    time_t _start_time = time(nullptr);
    boost::asio::ip::tcp::socket _socket;
    boost::asio::io_service & _main_service;

    abstract_session(boost::asio::io_service &, boost::asio::io_service &);
    virtual ~abstract_session();
    void start_read();
    virtual bool is_allowed(int16_t) const = 0;
    virtual void process_data(int16_t, byte_buffer &) = 0;
    virtual void handle_error();

private:
    std::array<uint8_t, 2> _header;
    int16_t _opcode;
    std::vector<uint8_t> _length, _raw_data;
    std::shared_ptr<byte_buffer> _packet;
    boost::asio::io_service::strand _strand;

    void close_socket();

    void handle_read_header(const boost::system::error_code &);
    void handle_read_length(const boost::system::error_code &);
    void handle_read_raw_data(const boost::system::error_code &);
    void handle_process_data(int16_t, std::shared_ptr<byte_buffer> &);
    void handle_write(const boost::system::error_code &,
                      std::shared_ptr<byte_buffer> &,
                      bool);

public:
    // helper method to translate dofus_unit to data readable by dofus client
    static void format(std::shared_ptr<byte_buffer> &, const network::dofus_unit &);

    // ::send writes immediately in the socket
    void send(const std::shared_ptr<byte_buffer> &, bool disconnect = false);
    void send(const network::dofus_unit &, bool disconnect = false);

    // ::write writes in a buffer, and ::flush calls ::send(buffer)
    void write(const network::dofus_unit &);
    void flush(bool disconnect = false);

    virtual void start() = 0;

    boost::asio::ip::tcp::socket & socket()
    { return _socket; }

    time_t start_time() const
    { return _start_time; }
};


#endif
