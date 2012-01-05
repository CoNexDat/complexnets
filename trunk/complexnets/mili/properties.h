/*
properties: A minimal library that implements object properties.
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

#ifndef PROPERTIES_H
#define PROPERTIES_H

NAMESPACE_BEGIN

template <class T, class Type, Type(T::*Getter)() const>
struct PropertyR
{
    operator Type() const
    {
        return (This()->*Getter)();
    }

private:
    const T* This() const
    {
        return reinterpret_cast<const T*>(this);
    }
};

template <class T, class Type, void (T::*Setter)(Type)>
struct PropertyW
{
    PropertyW<T, Type, Setter> operator = (Type t)
    {
        (This()->*Setter)(t);
        return *this;
    }

private:
    T* This()
    {
        return reinterpret_cast<T*>(this);
    }
};

template <class T, class Type, Type(T::*Getter)() const, void (T::*Setter)(Type)>
struct PropertyRW : PropertyR<T, Type, Getter>, PropertyW<T, Type, Setter>
{
    using PropertyW<T, Type, Setter>:: operator =;
};


#define BEGIN_PROPERTIES union {
#define END_PROPERTIES };

// alternate way:
#define PROPERTIES  union

#if 0
/* Not available */
template <class T, class Type, Type(T::*Member), Type(*Function)(Type)>
struct PropertyFR
{
    operator Type() const
    {
        return *Function(This()->*Member)();
    }

private:
    const T* This() const
    {
        return reinterpret_cast<const T*>(this);
    }
};

template <class T, class Type, Type(T::*Member), Type(*Function)(Type)>
struct PropertyFW
{
    void operator = (Type t)
    {
        (This()->*Member) = *Function(t);
    }

private:
    T* This()
    {
        return reinterpret_cast<T*>(this);
    }
};

template <class T, class Type, Type(T::*Member), Type(*FunctionR)(Type), Type(*FunctionW)(Type)>
struct PropertyFRW : PropertyFR<T, Type, Member, FunctionR>, PropertyFW<T, Type, Member, FunctionW>
{
    using PropertyFW<T, Type, Member, FunctionW>:: operator =;
};
#endif

NAMESPACE_END

#endif
