//
//  dofus_executor.hpp
//  core
//
//  Created by Alexandre Martin on 17/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef core_dofus_executor_hpp
#define core_dofus_executor_hpp

#include "../abstract_executor.hpp"
#include <ctime>

class byte_buffer;
class dofus_session;

namespace network
{
    class dofus_unit;
}

class dofus_executor : public abstract_executor
{
private:
    uint16_t _header;
    std::vector<uint8_t> _length, _raw_data;
    std::shared_ptr<byte_buffer> _packet;
    std::function<void()> _handle_error;

    void handle_read_header(const boost::system::error_code &, std::shared_ptr<dofus_session> &);
    void handle_read_length(const boost::system::error_code &, std::shared_ptr<dofus_session> &);
    void handle_read_raw_data(const boost::system::error_code &, std::shared_ptr<dofus_session> &);
    void handle_write(const boost::system::error_code &, std::shared_ptr<byte_buffer> &,
                      std::shared_ptr<dofus_session> &, bool);
public:
    dofus_executor(boost::asio::ip::tcp::socket &&, std::function<void()>);
    void start_read(std::shared_ptr<dofus_session>);

    // helper method to translate dofus_unit to data readable by dofus client
    static void format(std::shared_ptr<byte_buffer> &, const network::dofus_unit &);

    // ::send writes immediately in the socket
    void send(const std::shared_ptr<byte_buffer> &, std::shared_ptr<dofus_session>,
              bool disconnect = false);
    void send(const network::dofus_unit &, std::shared_ptr<dofus_session>,
              bool disconnect = false);

    // ::write writes in a buffer, and ::flush calls ::send(buffer)
    void write(const network::dofus_unit &);
    void flush(std::shared_ptr<dofus_session>, bool disconnect = false);
};

class dofus_session
{
    friend dofus_executor;
private:
    time_t _start_time = time(nullptr);

protected:
    dofus_executor _executor;
    bool _going_to_disconnect = false;

    virtual void handle_new_message(int16_t, std::shared_ptr<byte_buffer>) = 0;

public:
    dofus_session(boost::asio::ip::tcp::socket && socket, std::function<void()> handler)
        : _executor { std::move(socket), std::move(handler) }
    {

    }
    
    virtual void start() = 0;

    time_t start_time() const
    { return _start_time; }
};

#endif
