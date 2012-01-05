/*
delete_container: A minimal library for deleting the objects of a container of pointers.
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

#ifndef DELETE_CONTAINER_H
#define DELETE_CONTAINER_H

#include <algorithm>

NAMESPACE_BEGIN

template <class T>
struct deleter
{
    void operator()(T* tp) const
    {
        delete tp;
    }
};

template <class T>
struct pair_deleter
{
    void operator()(const T& p) const
    {
        delete p.second;
    }
};

/* Non-associative containers */
template <class T, class Alloc, template <class, class> class Container >
inline void delete_container(Container<T*, Alloc>& cont)
{
    for_each(cont.begin(), cont.end(), deleter<T>());
    cont.clear();
}

/* Sets  */
template <class T, class Comp, class Alloc, template <class, class, class> class Container >
inline void delete_container(Container<T*, Comp, Alloc>& cont)
{
    for_each(cont.begin(), cont.end(), deleter<T>());
    cont.clear();
}

/* Associative containers */
template <class Key, class T, class Comp, class Alloc, template <class, class, class, class> class Container >
inline void delete_container(Container<Key, T*, Comp, Alloc>& cont)
{
    for_each(cont.begin(), cont.end(), pair_deleter<typename Container<Key, T*, Comp, Alloc>::value_type >());
    cont.clear();
}

template <class T>
struct vector_deleter
{
    void operator()(T* tp) const
    {
        delete [] tp;
    }
};

template <class T>
struct vector_pair_deleter
{
    void operator()(const T& p) const
    {
        delete [] p.second;
    }
};

template <class T, class Alloc, template <class, class> class Container >
inline void vector_delete_container(Container<T*, Alloc>& cont)
{
    for_each(cont.begin(), cont.end(), vector_deleter<T>());
    cont.clear();
}

/* Sets */
template <class T, class Comp, class Alloc, template <class, class, class> class Container >
inline void vector_delete_container(Container<T*, Comp, Alloc>& cont)
{
    for_each(cont.begin(), cont.end(), vector_deleter<T>());
    cont.clear();
}

/* Associative containers */
template <class Key, class T, class Comp, class Alloc, template <class, class, class, class> class Container >
inline void vector_delete_container(Container<Key, T*, Comp, Alloc>& cont)
{
    for_each(cont.begin(), cont.end(), vector_pair_deleter<typename Container<Key, T*, Comp, Alloc>::value_type >());
    cont.clear();
}

template <class Container>
struct auto_delete_container : public Container
{
    ~auto_delete_container()
    {
        delete_container(static_cast<Container&>(*this));
    }
};

template <class Container>
struct auto_vector_delete_container : public Container
{
    ~auto_vector_delete_container()
    {
        vector_delete_container(static_cast<Container&>(*this));
    }
};

NAMESPACE_END

#endif
