//
//  pimpl.hpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef core_pimpl_hpp
#define core_pimpl_hpp

// see gotw c++11 updated pimpl idiom

template<class T>
class pimpl
{
private:
    std::unique_ptr<T> _ptr;
public:
    pimpl();
    template<class... Args> pimpl(Args && ...);
    ~pimpl();
    T * operator ->();
    const T * operator ->() const;
    T & operator *();
    const T & operator *() const;
};

#endif
