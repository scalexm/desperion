//
//  singleton.hpp
//  core
//
//  Created by Alexandre Martin on 29/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef core_singleton_hpp
#define core_singleton_hpp

#include "non_movable.hpp"
#include <cassert>

template<class T>
class singleton : non_movable // class inheriting from singleton is by default non_movable
{
protected:
    singleton() = default;
    ~singleton() = default;

public:
    template<class ... Args>
    static T & create(Args && ... args)
    {
        assert( !_singleton );
        _singleton.reset(new T { std::forward<Args>(args)... }); // raw new because of private ctors
        return *_singleton;
    }

    static void kill()
    {
        _singleton.reset(nullptr);
    }

    static T & instance()
    {
        assert( _singleton );
        return *_singleton;
    }

private:
    static std::unique_ptr<T> _singleton;
};

template<class T> std::unique_ptr<T> singleton<T>::_singleton;

#endif
