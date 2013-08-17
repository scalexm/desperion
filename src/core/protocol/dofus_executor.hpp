//
//  dofus_executor.hpp
//  core
//
//  Created by Alexandre Martin on 17/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef core_dofus_executor_hpp
#define core_dofus_executor_hpp

#include "../abstract_session.hpp"

class byte_buffer;

namespace network
{
    class dofus_unit;
}

struct network_message
{
    int16_t opcode;
    std::shared_ptr<byte_buffer> packet;
};

class dofus_executor;
using base_type = abstract_session<network_message, dofus_executor>;

class dofus_executor
{
private:
    uint16_t _header;
    std::vector<uint8_t> _length, _raw_data;
    std::shared_ptr<byte_buffer> _packet;

    void handle_read_header(const boost::system::error_code &, std::shared_ptr<base_type> &);
    void handle_read_length(const boost::system::error_code &, std::shared_ptr<base_type> &);
    void handle_read_raw_data(const boost::system::error_code &, std::shared_ptr<base_type> &);
    void handle_write(const boost::system::error_code &,
                      std::shared_ptr<byte_buffer> &,
                      std::shared_ptr<base_type> &,
                      bool);
public:
    dofus_executor() = default;
    void start_read(std::shared_ptr<base_type>);

    // helper method to translate dofus_unit to data readable by dofus client
    static void format(std::shared_ptr<byte_buffer> &, const network::dofus_unit &);

    // ::send writes immediately in the socket
    void send(const std::shared_ptr<byte_buffer> &, std::shared_ptr<base_type>,
              bool disconnect = false);
    void send(const network::dofus_unit &, std::shared_ptr<base_type>,
              bool disconnect = false);

    // ::write writes in a buffer, and ::flush calls ::send(buffer)
    void write(const network::dofus_unit &);
    void flush(std::shared_ptr<base_type>,
               bool disconnect = false);
};

#endif
