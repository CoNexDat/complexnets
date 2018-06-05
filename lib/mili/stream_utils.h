/*
stream_utils: A minimal library that provides CSV and other file/stream
    functionalities..
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

#ifndef STREAM_UTILS_H
#define STREAM_UTILS_H

#include <vector>
#include <list>
#include <set>
#include <iostream>
#include <string>
#include "string_utils.h"
#include "container_utils.h"

NAMESPACE_BEGIN

//------------ Separator

template <class Container>
struct _Separator
{
    Container& v;
    const char s;

    _Separator(Container& v, char s)
        : v(v), s(s)
    {}

    _Separator(const _Separator& other)
        : v(other.v), s(other.s)
    {}
};

template <class Container>
inline _Separator<Container> Separator(Container& v, char s)
{
    return _Separator<Container>(v, s);
}

//------------ Output

template <class Container>
inline void _mili_base_output(std::ostream& os, const Container& v, char separator)
{
    const size_t max = v.size();

    if (max > 0)    /* This is done for optimization purposes.  */
    {
        typename Container::const_iterator it = v.begin();

        /* Print the first value */
        os << *it;

        /* Prints the following values */
        for (++it; it != v.end(); ++it)
            os << separator << *it;
    }
}

//------------ Operator <<

/* This works for vectors and lists */
template < class T, class Alloc, template <class, class> class Container>
inline std::ostream& operator << (std::ostream& os, const Container<T, Alloc>& v)
{
    _mili_base_output(os, v, ',');    /* By default uses a comma as a separator */
    return os;
}

/* This work for sets */
template <class Key, class Comp, class Alloc>
inline std::ostream& operator << (std::ostream& os, const std::set<Key, Comp, Alloc>& v)
{
    _mili_base_output(os, v, ',');    /* By default uses a comma as a separator */
    return os;
}

/* This works for _Separator
(Receives container and separator through a _Separator type) */
template <class Container>
inline std::ostream& operator << (std::ostream& os, const _Separator<Container>& s)
{
    _mili_base_output(os, s.v, s.s);
    return os;
}

//------------ Input

template <class Container>
inline void _mili_base_input(std::istream& is, Container& v)
{
    typename Container::value_type t;
    std::string line;

    /* Extracts characters from is and stores them into line
    until a delimitation character is found. (\n) */
    if (std::getline(is, line))
    {
        char sep;

        /* provides an interface to manipulate strings
        as if they were input/output streams. */
        std::stringstream ss(line);

        do
        {
            while (ss >> t)
                insert_into(v, t);

            ss.clear();
        }
        while (ss >> sep);
    }
}

//------------ Operator >>

/* This works for vectors and lists */
template <class T, class Alloc, template <class, class> class Container>
inline std::istream& operator >> (std::istream& is, Container<T, Alloc>& v)
{
    _mili_base_input(is, v);
    return is;
}

/* This works for sets */
template <class Key, class Comp, class Alloc>
inline std::istream& operator >> (std::istream& is, std::set<Key, Comp, Alloc>& v)
{
    _mili_base_input(is, v);
    return is;
}

/* This works for _Separator
(Receives container and separator through a _Separator type) */
template <class T>
inline std::istream& operator >> (std::istream& is, const _Separator<T>& s)
{
    std::string line;

    if (std::getline(is, line))
    {
        std::string::size_type last_pos = 0, pos;
        bool found;

        do
        {
            pos = line.find(s.s, last_pos);
            found = (pos !=  std::string::npos);
            if (found)
            {
                insert_into(s.v,
                            /* Converts from string to type T */
                            from_string<typename T::value_type>(
                                line.substr(last_pos, pos - last_pos)
                            )
                           );

                last_pos = pos + 1;
            }
        }
        while (found);

        if (last_pos != std::string::npos)
            insert_into(s.v,
                        from_string<typename T::value_type>(
                            line.substr(last_pos)
                        )
                       );
    }

    return is;
}

NAMESPACE_END

#endif
