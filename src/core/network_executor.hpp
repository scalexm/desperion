//
//  network_executor.hpp
//  core
//
//  Created by Alexandre Martin on 02/03/2014.
//  Copyright (c) 2014 alexm. All rights reserved.
//

#ifndef core_network_executor_hpp
#define core_network_executor_hpp

#include "non_movable.hpp"
#include <boost/asio.hpp>

class abstract_session;
class byte_buffer;

namespace protocol { class dofus_unit; }

class network_executor : non_movable
{
public:
    using error_handler = std::function<void(const boost::system::error_code &)>;
    using message_handler = std::function<void(int16_t, std::shared_ptr<byte_buffer>)>;
private:
    boost::asio::ip::tcp::socket _socket;
    boost::asio::io_service::strand _strand;
    uint16_t _header;
    std::vector<uint8_t> _length, _raw_data;
    std::shared_ptr<byte_buffer> _packet;

    error_handler _handle_error;
    message_handler _handle_message;

    void handle_read_header(const boost::system::error_code &, std::shared_ptr<abstract_session> &);
    void handle_read_length(const boost::system::error_code &, std::shared_ptr<abstract_session> &);
    void handle_read_raw_data(const boost::system::error_code &,
                              std::shared_ptr<abstract_session> &);

    // std::shared_ptr<byte_buffer> must outlive write execution
    void handle_write(const boost::system::error_code &, std::shared_ptr<byte_buffer> &,
                      std::shared_ptr<abstract_session> &, bool);

    void close_socket();

public:
    network_executor(boost::asio::ip::tcp::socket && socket, error_handler, message_handler);
    ~network_executor();

    void start_read(std::shared_ptr<abstract_session>);
    
    void write(const byte_buffer &);
    void write(const protocol::dofus_unit &);
    bool flush(std::shared_ptr<abstract_session>, bool);

    const boost::asio::ip::tcp::socket & socket() const
    { return _socket; }
};

#endif
