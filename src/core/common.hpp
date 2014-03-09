//
//  common.hpp
//  core
//
//  Created by Alexandre Martin on 29/07/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#ifndef core_common_hpp
#define core_common_hpp

#define _WIN32_WINNT NTDDI_WIN7
#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include <stdexcept>
#include <memory>
#include <cstdint> // integral types


/* part of c++14 */
namespace std
{
	template<class T, class ... Args>
	std::unique_ptr<T> make_unique(Args && ... args)
	{
		return std::unique_ptr<T> { new T { std::forward<Args>(args)... } };
	}
}

constexpr int SHARED_VERSION_MAJOR = 1,
    SHARED_VERSION_MINOR = 0,
    SHARED_VERSION_RELEASE = 0;

using std::end;
using std::begin;

#endif
