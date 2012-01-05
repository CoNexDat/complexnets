/*
type_mapper: A minimal library that implements a type mapper.
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

#ifndef TYPE_MAPPER_H
#define TYPE_MAPPER_H

NAMESPACE_BEGIN

#define declare_type_mapper(name)   \
    template <class From>           \
    struct name                     \
    {                               \
        typedef From type;          \
    }

#define add_mapping(mapper, from_type, to_type) \
    template<>                                  \
    struct mapper<from_type>                    \
    {                                           \
        typedef to_type type;                   \
    }

#define add_mapping_for_pointers(mapper, to_type)   \
    template <class From>                           \
    struct mapper<From*>                            \
    {                                               \
        typedef to_type type;                       \
    }

#define add_mapping_const_removal(mapper)           \
    template <class From>                           \
    struct mapper<const From>                       \
    {                                               \
        typedef typename mapper<From>::type type;   \
    }

#define add_mapping_ref_removal(mapper)             \
    template <class From>                           \
    struct mapper<From&>                            \
    {                                               \
        typedef typename mapper<From>::type type;   \
    }

#define map_type_(mapper, from_type) mapper<from_type>::type
#define map_type(mapper, from_type) typename map_type_(mapper, from_type)

// Some useful mappers:

// Removes const and &:
declare_type_mapper(BasicType);
add_mapping_const_removal(BasicType);
add_mapping_ref_removal(BasicType);

NAMESPACE_END

#endif
