
/*
    Copyright (C) 2011, Hugo Arregui, FuDePAN

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

#ifndef METAPROGRAMMING_UTILS_H
#define METAPROGRAMMING_UTILS_H

#include "template_info.h"

NAMESPACE_BEGIN

template <bool COND, class T, class F>
struct Select
{
    typedef F result;
};

template <class T, class F>
struct Select<true, T, F>
{
    typedef T result;
};

template <class T>
struct ParameterType
{
    typedef template_info<T> info;
    typedef typename Select < info::is_pointer || info::is_native || info::is_reference, T, const T& >::result type;
};

NAMESPACE_END

#endif
