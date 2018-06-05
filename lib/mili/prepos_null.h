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

    This is the NULL action, useful when you want to do only
    a pre-call and not a post-call, or viceversa.
*/

#ifndef PREPOS_NULL_H
#define PREPOS_NULL_H

struct PrePosNull
{
    void operator()() const { }
};

#endif
