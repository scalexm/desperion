//
//  scope_guard.hpp
//  core
//
//  Created by Alexandre Martin on 30/07/13.
//  Copyright (c) 2013-2014 scalexm. All rights reserved.
//

#ifndef core_scope_guard_hpp
#define core_scope_guard_hpp

template<class Fun>
class scope_guard
{
private:
    Fun _fun;
    bool _dismissed = false;

public:
    explicit scope_guard(const Fun & fun) : _fun { fun }
    {

    }

    scope_guard(scope_guard && that) : _fun { that._fun }, _dismissed { that._dismissed }
    {
        that.dismiss();
    }


    scope_guard & operator =(scope_guard && that)
    {
        _fun = that._fun;
        _dismissed = that._dismissed;
        that.dismiss();
    }

    scope_guard(const scope_guard &) = delete;
    scope_guard & operator =(const scope_guard &) = delete;

    void dismiss() noexcept
    {
        _dismissed = true;
    }

    ~scope_guard()
    {
        if (!_dismissed)
            _fun();
    }
};

template <typename Fun>
scope_guard<Fun> make_scope_guard(const Fun & fun)
{
    return scope_guard<Fun>(fun);
}

#endif
