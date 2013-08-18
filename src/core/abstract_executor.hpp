//
//  abstract_executor.hpp
//  core
//
//  Created by Alexandre Martin on 18/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef core_abstract_executor_hpp
#define core_abstract_executor_hpp

#include <boost/asio.hpp>

class abstract_executor
{
protected:
    boost::asio::ip::tcp::socket _socket;
    boost::asio::io_service::strand _strand;

    void close_socket()
    {
        if (_socket.is_open())
        {
            boost::system::error_code ec;
            _socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
            _socket.close(ec);
        }
    }

public:
    abstract_executor(boost::asio::ip::tcp::socket && socket)
        : _socket { std::move(socket) }, _strand { _socket.get_io_service() }
    {
    }

    virtual ~abstract_executor()
    {
        close_socket();
    }

    const boost::asio::ip::tcp::socket & socket() const
    { return _socket; }    
};

#endif
