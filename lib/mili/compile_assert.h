/*
compile_assert: A minimal library supporting compile time (static) assertions,
    a la C++0x.
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

#ifndef COMPILE_ASSERT_H
#define COMPILE_ASSERT_H

//NAMESPACE_BEGIN

#ifndef __GXX_EXPERIMENTAL_CXX0X__  // replace this by __cplusplus > 199711L when available

#define declare_static_assert(name)     \
template <bool Condition>               \
struct name                             \
{                                       \
    typedef int CompileTimeAssertion;   \
};                                      \
template <>                             \
struct name<false>                      \
{}

#define compile_assert(condition, name) \
    typedef name<condition >::CompileTimeAssertion name##__

#define template_compile_assert(condition, name) \
    typedef typename name<condition >::CompileTimeAssertion name##__

declare_static_assert(GenericAssertion);

#define generic_assert(condition)   \
    compile_assert(condition, GenericAssertion)

#define template_generic_assert(condition)   \
    compile_assert(condition, GenericAssertion)

#else
#   define declare_static_assert(name)
#   define compile_assert(condition, name) static_assert(condition, #name)
#   define template_compile_assert(condition, name) static_assert(condition, #name)
#   define generic_assert(condition) static_assert(condition, #condition)
#   define template_generic_assert(condition) static_assert(condition, #condition)
#endif

//NAMESPACE_END

#endif

