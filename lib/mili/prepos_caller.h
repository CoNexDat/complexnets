/*
prepos_caller: A minimal library for wrapping object methods calls.
    Copyright (C) 2008, 2009  Daniel Gutson, FuDePAN

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

    This is the main class. Use it passing the pre-call and pos-call.
*/

#ifndef PREPOS_H
#define PREPOS_H

NAMESPACE_BEGIN

template <class T, class Pre, class Pos>
struct PrePosCaller
{
    struct Temp
    {
        T& t;
        Pos& pos;

        Temp(T& t, Pos& pos) : t(t), pos(pos) {}

        T& operator -> () const
        {
            return t;
        }

        ~Temp()
        {
            pos();
        }
    };

    T& t;
    Pre& pre;
    Pos& pos;

    PrePosCaller(T& t, Pre& pre, Pos& pos) : t(t), pre(pre), pos(pos) {}

    Temp operator -> () const
    {
        pre();
        return Temp(t, pos);
    }
};

template <class T, class Pre, class Pos>
struct PrePosCaller<T*, Pre, Pos>
{
    struct Temp
    {
        T* t;
        Pos& pos;

        Temp(T* t, Pos& pos) : t(t), pos(pos) {}

        T* operator -> () const
        {
            return t;
        }

        ~Temp()
        {
            pos();
        }
    };

    T* t;
    Pre& pre;
    Pos& pos;

    PrePosCaller(T* t, Pre& pre, Pos& pos) : t(t), pre(pre), pos(pos) {}

    Temp operator -> () const
    {
        pre();
        return Temp(t, pos);
    }
};

template <class T, class Pre, class Pos>
struct PrePosCaller<T* const, Pre, Pos>
{
    struct Temp
    {
        T* const t;
        Pos& pos;
        Temp(T* t, Pos& pos) : t(t), pos(pos) {}

        T* operator -> () const
        {
            return t;
        }

        ~Temp()
        {
            pos();
        }
    };

    T* const t;
    Pre& pre;
    Pos& pos;

    PrePosCaller(T* t, Pre& pre, Pos& pos) : t(t), pre(pre), pos(pos) {}

    Temp operator -> () const
    {
        pre();
        return Temp(t, pos);
    }
};

NAMESPACE_END

#endif
