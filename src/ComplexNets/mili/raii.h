/*
raii.h: A minimal library to provide the RAII feature
    Copyright (C) 2011 Lucas Besso & Raul Striglio, UNRC

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

#ifndef RAII_H
#define RAII_H

NAMESPACE_BEGIN

template <class T, void (T::*M)(void)>
class RAII
{

public:
    RAII(T& inst) : _var(inst) {}
    ~RAII()
    {
        (_var.*M)();
    }

private:
    T& _var;
};

NAMESPACE_END

#endif
