//
//  auth_queue.hpp
//  core
//
//  Created by Alexandre Martin on 09/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef core_auth_queue_hpp
#define core_auth_queue_hpp

#include <queue>
#include <thread>
#include <functional>
#include <boost/asio.hpp>

template<class Session, class Packet>
class auth_queue
{
public:
    using pair_type = std::pair<std::weak_ptr<Session>, std::shared_ptr<Packet>>;
private:
    std::queue<pair_type> _sessions;
    size_t _counter = 0;
    void (Session::*_function)(const std::shared_ptr<Packet> &);

public:
    explicit auth_queue(void (Session::*function)(const std::shared_ptr<Packet> &))
        : _function { function }
    {
    }

    size_t counter() const
    { return _counter; }

    size_t size() const
    { return _sessions.size(); }
    
    void next()
    {
        while (!_sessions.empty())
        {
            auto && pair = _sessions.front();
            auto session = pair.first.lock();
            if (!session)
            {
                _sessions.pop();
                continue;
            }
            std::thread { std::bind(_function, session, std::move(pair.second)) }.detach();
            _sessions.pop();
            break;
        }
    }

    std::pair<size_t, size_t> push(pair_type && pair, boost::asio::io_service & main_service)
    {
        auto empty = _sessions.empty();
        _sessions.push(std::move(pair));
        if (empty)
            main_service.post(std::bind(&auth_queue::next, this));
        return { _sessions.size(), _counter };
    }
};

#endif
