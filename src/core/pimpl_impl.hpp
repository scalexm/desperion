//
//  pimpl_impl.hpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef core_pimpl_impl_hpp
#define core_pimpl_impl_hpp

// see gotw c++11 updated pimpl idiom

template<class T> pimpl<T>::pimpl() : _ptr { std::make_unique<T>() }
{
}

template<class T> template<class ... Args>
pimpl<T>::pimpl(Args && ... args ) : _ptr { std::make_unique<T>(std::forward<Args>(args)...) }
{
}

template<class T> pimpl<T>::~pimpl()
{
    //  willingly empty
}

template<class T> T * pimpl<T>::operator ->()
{ return _ptr.get(); }

template<class T> T & pimpl<T>::operator *()
{ return *_ptr.get(); }

template<class T> const T * pimpl<T>::operator ->() const
{ return _ptr.get(); }

template<class T> const T & pimpl<T>::operator *() const
{ return *_ptr.get(); }

#endif
