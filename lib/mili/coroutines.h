/*
coroutines: A minimal library that implements coroutines.
    Copyright (C) 2010  Daniel Gutson, FuDePAN

    This file is part of the MiLi Minimalistic Library.

    MiLi is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    MiLi is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with MiLi.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef COROUTINES_H
#define COROUTINES_H

NAMESPACE_BEGIN

class Coroutine
{
protected:
    int yield_point;
public:
    Coroutine() : yield_point(0) {}
};

#define BEGIN_COROUTINE     \
    switch(yield_point)     \
    {                       \
        case 0:

#define mili_yield(value)       \
    do                          \
    {                           \
        yield_point = __LINE__; \
        return (value);         \
        case __LINE__:;         \
    }                           \
    while(0)

// exit_coroutine breaks the structure and is discouraged.
#define exit_coroutine(ret) \
    do                      \
    {                       \
        yield_point = 0;    \
        return (ret);       \
    }                       \
    while(0)

#define END_COROUTINE(ret)  \
    }                       \
    exit_coroutine(ret)

NAMESPACE_END

#endif

