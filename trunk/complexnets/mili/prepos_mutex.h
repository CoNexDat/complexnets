/*
prepos_caller: A minimal library for wrapping object methods calls.
    Copyright (C) 2008, 2009  Daniel Gutson, FuDePAN

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

    This file provides the pre-call and pos-call actions to lock/unlock
    a pthread mutex, respectivelly.
*/

#ifndef PREPOS_MUTEX_H
#define PREPOS_MUTEX_H

#include <pthread.h>

struct PreMutex
{
    pthread_mutex_t* const mutex;

    PreMutex(pthread_mutex_t* mutex) : mutex(mutex) {}
    PreMutex(const PreMutex& other) : mutex(other.mutex) {}

    void operator()() const
    {
        pthread_mutex_lock(mutex);
    }
};

struct PosMutex
{
    pthread_mutex_t* const mutex;

    PosMutex(pthread_mutex_t* mutex) : mutex(mutex) {}
    PosMutex(const PosMutex& other) : mutex(other.mutex) {}

    void operator()() const
    {
        pthread_mutex_unlock(mutex);
    }
};

#endif
