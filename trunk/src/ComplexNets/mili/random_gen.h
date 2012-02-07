/*
random_gen.h: A minimal library for generating random numbers.
    Copyright (C) 2010 Daniel Gutson, FuDePAN

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

#ifndef RANDOM_GEN_H
#define RANDOM_GEN_H

#include <stdlib.h>
#ifdef _WIN32
#    include <Windows.h>
#    include <time.h>
#    undef min
#    undef max
#else
#    include <sys/time.h>
#endif

NAMESPACE_BEGIN

class TimeBasedSeedPolicy
{
protected:
    unsigned int seed;

    TimeBasedSeedPolicy(unsigned int seed) :
        seed(seed)
    {}

    TimeBasedSeedPolicy()
    {
#ifdef _WIN32
        FILETIME ft;
        GetSystemTimeAsFileTime(&ft);
        seed = ft.dwLowDateTime;
#else
        struct timeval tv;
        gettimeofday(&tv, NULL);
        seed = tv.tv_usec;
#endif
    }
};

#ifndef _WIN32
struct AutonomousSeedPolicy : TimeBasedSeedPolicy
{
    AutonomousSeedPolicy(unsigned int seed) :
        TimeBasedSeedPolicy(seed)
    {}

    AutonomousSeedPolicy() :
        TimeBasedSeedPolicy()
    {}

    int get()
    {
        return rand_r(&seed);
    }
};
#endif

struct GlobalSeedPolicy : TimeBasedSeedPolicy
{
    GlobalSeedPolicy() :
        TimeBasedSeedPolicy()
    {
        srand(seed);
    }

    GlobalSeedPolicy(unsigned int seed) :
        TimeBasedSeedPolicy(seed)
    {
        srand(seed);
    }

    int get()
    {
        return rand();
    }
};

#ifdef _WIN32
typedef GlobalSeedPolicy DefaultSeedPolicy;
#else
typedef AutonomousSeedPolicy DefaultSeedPolicy;
#endif

// this is for integral values
template < class T, class SeedPolicy = DefaultSeedPolicy >
class Randomizer
{
    SeedPolicy policy;
    const T min;
    const int width;
public:
    Randomizer(T min, T max) :
        policy(),
        min(min),
        width(int(max - min) + 1)
    {}

    Randomizer(T min, T max, unsigned int seed) :
        policy(seed),
        min(min),
        width(int(max - min) + 1)
    {}

    T get()
    {
        return T(policy.get() % width) + min;
    }
};

#define SPECIALIZE_RND(T)                           \
template <class SeedPolicy>                         \
class Randomizer<T, SeedPolicy>                     \
{                                                   \
    SeedPolicy policy;                              \
    const T min;                                    \
    const T factor;                                 \
public:                                             \
    Randomizer(T min, T max) :                      \
        policy(),                                   \
        min(min),                                   \
        factor((max-min)/T(RAND_MAX))               \
    {                                               \
    }                                               \
                                                    \
    Randomizer(T min, T max, unsigned int seed) :   \
        policy(seed),                               \
        min(min),                                   \
        factor((max-min)/T(RAND_MAX))               \
    {                                               \
    }                                               \
                                                    \
    T get()                                         \
    {                                               \
        return T(policy.get()) * factor + min;      \
    }                                               \
}

SPECIALIZE_RND(float);
SPECIALIZE_RND(double);

#undef SPECIALIZE_RND

NAMESPACE_END

#endif
