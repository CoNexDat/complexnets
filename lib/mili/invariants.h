/*
invariants: A minimal library for a checking invariants.
    Copyright (C) 2009  Daniel Gutson, FuDePAN

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

#ifndef INVARIANTS_H
#define INVARIANTS_H

#include <exception>

NAMESPACE_BEGIN

struct InvariantNotMet : std::exception
{
};

/* Part 1: Invariants for parameters */

namespace invariant
{
// this will be a template alias in C++0x
#define define_invariant(Name, op)              \
    template <class T, T operand>               \
    class Name                                  \
    {                                           \
            const T value;                      \
        public:                                 \
            operator T()const { return value; } \
            Name(T value) : value(value)        \
            {                                   \
                if (!(value op operand))        \
                    throw InvariantNotMet();    \
            }                                   \
    }

define_invariant(lt, <);
define_invariant(le, <=);
define_invariant(eq, ==);
define_invariant(ne, !=);
define_invariant(ge, >=);
define_invariant(gt, >);

template <class T>
class NeverNull
{
    T* const ptr;
public:
    NeverNull(T* ptr) : ptr(ptr)
    {
        if (ptr == NULL)
            throw InvariantNotMet();
    }
    operator T* () const
    {
        return ptr;
    }
};

template <class T, T Min, T Max>
struct InRange : ge<T, Min>, le<T, Max>
{
    InRange(T t) : ge<T, Min>(t), le<T, Max>(t) {}
};
}

/* Part 2: Class Invariants */
/* This is implemented using the prepos_caller technique. */

template <class T, bool (*Invariant)(const T&)>
class InvariantClass
{
    T& t;
public:
    struct Temp
    {
        T& t;
        Temp(T& t) : t(t) {}
        T* operator -> () const
        {
            return &t;
        }

        ~Temp()
        {
            if (!Invariant(t))
                throw InvariantNotMet();
        }
    };

    InvariantClass(T& t) : t(t) {};

    Temp operator -> () const
    {
        return Temp(t);
    }
};

NAMESPACE_END

#endif
