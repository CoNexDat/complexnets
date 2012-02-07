/*
    template_info: A minimal library to obtain type information of a template
    parameter.
    Copyright (C) 2009  Daniel Gutson, FuDePAN; 2011 Hugo Arregui, FuDePAN

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

#ifndef TEMPLATE_INFO_H
#define TEMPLATE_INFO_H

NAMESPACE_BEGIN

template <class T>
struct Unconst
{
    typedef T type;
};

template <class T>
struct Unconst<const T>
{
    typedef T type;
};

template <class T>
struct Unconst<const T&>
{
    typedef T& type;
};

template <class T>
struct Unconst<T* const>
{
    typedef T* type;
};

template <class T1, class T2>
struct type_equal
{
    enum {  value = 0   };
};
template <class T>
struct type_equal<T, T>
{
    enum {  value = 1   };
};

#define _declare_template_attribute(name,attribute) \
template <class T>                                  \
struct template_##name                              \
{                                                   \
    enum {  value = 0   };                          \
};                                                  \
template <class T>                                  \
struct template_##name<attribute>                   \
{                                                   \
    enum {  value = 1   };                          \
}

_declare_template_attribute(is_unconst_pointer, T*);
_declare_template_attribute(is_reference, T&);
_declare_template_attribute(is_volatile, volatile T);

#undef _declare_template_attribute

template <class T>
struct template_is_pointer
{
    enum { value = template_is_unconst_pointer<typename Unconst<T>::type>::value };
};

template <class E>
struct template_is_integral
{
    typedef typename Unconst<E>::type T;
    enum
    {
        value =
            type_equal<T, int>::value       || type_equal<T, unsigned int>::value ||
        type_equal<T, short int>::value || type_equal<T, unsigned short int>::value ||
        type_equal<T, long int>::value  || type_equal<T, unsigned long int>::value ||
        type_equal<T, char>::value      || type_equal<T, unsigned char>::value || type_equal<T, signed char>::value
    };
};

template <class E>
struct template_is_native
{
    typedef typename Unconst<E>::type T;
    enum
    {
        value =
            template_is_integral<T>::value ||
            type_equal<T, bool>::value     ||
        type_equal<T, float>::value    ||
        type_equal<T, double>::value
    };
};

template<class T>
struct template_is_basic_string
{
    enum { value = type_equal<typename Unconst<T>::type, std::string>::value };
};

template <class T>
struct template_is_container
{
    enum {  value = 0   };
};
#define _declare_template_container(cont)         \
template <class T>                                \
struct template_is_container<std::cont<T> >       \
{                                                 \
    enum {  value = 1   };                        \
};                                                \
template <class T>                                \
struct template_is_container<const std::cont<T> > \
{                                                 \
    enum {  value = 1   };                        \
}

#define _declare_template_container_assoc(cont)      \
template <class K, class D>                          \
struct template_is_container<std::cont<K, D> >       \
{                                                    \
    enum {  value = 1   };                           \
};                                                   \
template <class K, class D>                          \
struct template_is_container<const std::cont<K, D> > \
{                                                    \
    enum {  value = 1   };                           \
}

_declare_template_container(vector);
_declare_template_container(list);
_declare_template_container(set);
_declare_template_container(multiset);
_declare_template_container_assoc(map);
_declare_template_container_assoc(multimap);

#undef _declare_template_container
#undef _declare_template_container_assoc

template<class T>
struct template_is_const
{
    enum {value = !type_equal<T, typename Unconst<T>::type>::value  };
};

// this encapsulates all
template <class T>
struct template_info
{
    enum { is_pointer      = template_is_pointer<T>::value };
    enum { is_reference    = template_is_reference<T>::value };
    enum { is_const        = template_is_const<T>::value };
    enum { is_volatile     = template_is_volatile<T>::value };
    enum { is_integral     = template_is_integral<T>::value };
    enum { is_native       = template_is_native<T>::value };
    enum { is_container    = template_is_container<T>::value };
    enum { is_basic_string = template_is_basic_string<T>::value };
    enum { size = sizeof(T) };

    template <class T2>
    struct is_equal_to
    {
        enum { value = type_equal<T, T2>::value };
    };

    template <class T2>
    struct is_smaller_than
    {
        enum { value = (sizeof(T) < sizeof(T2)) };
    };

    template <class T2>
    struct is_greater_than
    {
        enum { value = (sizeof(T) > sizeof(T2)) };
    };

    template <class T2>
    struct is_same_size
    {
        enum { value = (sizeof(T) == sizeof(T2)) };
    };
};

NAMESPACE_END

#endif

