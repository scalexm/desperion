//
//  sql_error.hpp
//  core
//
//  Created by Alexandre Martin on 04/08/13.
//  Copyright (c) 2013 alexm. All rights reserved.
//

#ifndef core_sql_error_hpp
#define core_sql_error_hpp

#include <string>

class sql_error : public std::runtime_error
{
public:
	explicit sql_error(const std::string & str) : std::runtime_error { str }
	{
	}
};

#endif
