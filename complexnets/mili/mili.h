/*
MiLi: A set of minimal libraries composed only by 1 header file each.
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

    This is the main include file.
*/

#ifndef MILI_H
#define MILI_H

#ifdef MILI_NAMESPACE
#define NAMESPACE_BEGIN namespace mili {
#define NAMESPACE_END }
#else
#define NAMESPACE_BEGIN
#define NAMESPACE_END
#endif

#ifndef NO_BITWISE_ENUMS
#   include "bitwise_enums.h"
#endif

#ifndef NO_PREPOS_CALLER
#   include "prepos_caller.h"
#endif

#ifndef NO_DELETE_CONTAINER
#   include "delete_container.h"
#endif

#ifndef NO_PROMOTION_DISABLE
#   include "promotion_disable.h"
#endif

#ifndef NO_FACTORY
#   include "factory.h"
#endif

#ifndef NO_INVARIANTS
#   include "invariants.h"
#endif

#ifndef NO_TYPE_MAPPER
#   include "type_mapper.h"
#endif

#ifndef NO_PROPERTIES
#   include "properties.h"
#endif

#ifndef NO_STRING_UTILS
#   include "string_utils.h"
#endif

#ifndef NO_RANKER
#   include "ranker.h"
#endif

#ifndef NO_VARIANTS_SET
#   include "variants_set.h"
#endif

#ifndef NO_CONTAINER_UTILS
#   include "container_utils.h"
#endif

#ifndef NO_STREAM_UTILS
#   include "stream_utils.h"
#endif

#ifndef NO_ARITH_UTILS
#   include "arith_utils.h"
#endif

#ifndef NO_RANDOM_GEN
#   include "random_gen.h"
#endif

#ifndef NO_LOOP_UNROLLING
#   include "loop_unrolling.h"
#endif

#ifndef NO_COMPILE_ASSERT
#   include "compile_assert.h"
#endif

#ifndef NO_TEMPLATE_INFO
#   include "template_info.h"
#endif

#ifndef NO_BINSTREAMS
#   include "binary_streams.h"
#endif

#ifndef NO_COROUTINES
#   include "coroutines.h"
#endif

#ifndef NO_FAST_LIST
#   include "fast_list.h"
#endif

#ifndef NO_GENERIC_EXCEPTION
#   include "generic_exception.h"
#endif

#ifndef NO_RAII
#   include "raii.h"
#endif

#ifndef NO_AUTO_ARRAY
#   include "auto_array.h"
#endif

#ifndef NO_METAPROGRAMMING_UTILS
#   include "metaprogramming_utils.h"
#endif

#ifndef NO_NON_COPYABLE
#   include "non_copyable.h"
#endif

#undef NAMESPACE_BEGIN
#undef NAMESPACE_END

#endif
