//
//  non_movable.hpp
//  core
//
//  Created by Alexandre Martin on 29/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef core_non_movable_hpp
#define core_non_movable_hpp

struct non_movable
{
protected:
    non_movable() = default;

public:
    non_movable(const non_movable &) = delete;
    const non_movable & operator =(const non_movable &) = delete;
    non_movable(non_movable &&) = delete;
    const non_movable & operator =(non_movable &&) = delete;
};

#endif
