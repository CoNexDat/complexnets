/*
    auto_array: an auto_ptr counterpart for array objects
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

#ifndef AUTO_ARRAY_H
#define AUTO_ARRAY_H

NAMESPACE_BEGIN

template <class T>
class auto_array
{
public:
    auto_array(T* _array) :
        array(_array)
    {}

    ~auto_array()
    {
        release();
    }

    T* get() const
    {
        return array;
    }

    T& operator[](size_t n)
    {
        return array[n];
    }

    const T& operator[](size_t n) const
    {
        return array[n];
    }

    auto_array<T>& operator=(const auto_array<T>& b)
    {
        reset(b.array);
        return *this;
    }

    void reset(T* _array)
    {
        release();
        array = _array;
    }

    T* release()
    {
        T* const tmp = array;
        delete[] array;
        array = NULL;
        return tmp;
    }
private:
    T* array;
};


NAMESPACE_END

#endif
