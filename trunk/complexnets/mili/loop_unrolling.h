/*
loop_unrolling: A minimal library for TMP loop unrolling.
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

#ifndef LOOP_UNROLLING_H
#define LOOP_UNROLLING_H

NAMESPACE_BEGIN

template <bool Unroll, unsigned int N, class Operation>
struct _FOR
{
    static void iterate(Operation& op)
    {
        op();
        _FOR < Unroll, N - 1, Operation >::iterate(op);
    }
};

template <bool Unroll, class Operation>
struct _FOR<Unroll, 0, Operation>
{
    static void iterate(Operation&)
    {}
};

template <unsigned int N, class Operation>
struct _FOR<false, N, Operation>
{
    static void iterate(Operation& op)
    {
        for (unsigned int i = 0; i < N; ++i)
            op();
    }
};

struct UnrollAlwaysClause
{
    template <unsigned int N>
    struct clause
    {
        enum { unroll = true };
    };
};

template <unsigned int MAX>
struct UnrollUpToClause
{
    template <unsigned int N>
    struct clause
    {
        enum { unroll = (N <= MAX) };
    };
};

template < unsigned int N, class Operation, class UnrollClause = UnrollAlwaysClause >
struct FOR
{
    static void iterate(Operation& op)
    {
        typedef typename UnrollClause::template clause<N> clause;
        _FOR<clause::unroll, N, Operation>::iterate(op);
    }
};

NAMESPACE_END

#endif
