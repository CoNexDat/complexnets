/*
generic_exception.h: A minimal library for generic exceptions.
    Copyright (C) 2010  Daniel Gutson, FuDePAN

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

#ifndef GENERIC_EXCEPTION
#define GENERIC_EXCEPTION

#include <exception>
#include <string>

NAMESPACE_BEGIN

template <class Hierarchy>
class GenericException : public std::exception
{
protected:
    const std::string description;

public:
    explicit GenericException(const std::string& description) :
        description(description)
    {}

    ~GenericException() throw() {};

    //! what redefinition
    virtual const char* what() const throw()
    {
        return description.c_str();
    }
};

#ifdef MILI_NAMESPACE
#    define EXCEPTION_NAMESPACE mili
#else
#    define EXCEPTION_NAMESPACE
#endif

#define DEFINE_SPECIFIC_EXCEPTION(name, subtype)                     \
class name : public EXCEPTION_NAMESPACE::GenericException<subtype>   \
{                                                                    \
public:                                                              \
    name() :                                                         \
        GenericException<subtype>(#name)                             \
    {}                                                               \
                                                                     \
    name(const std::string& description) :                           \
        GenericException<subtype>(#name ": " + description)          \
    {}                                                               \
}

#define DEFINE_SPECIFIC_EXCEPTION_TEXT(name, subtype, text)          \
class name : public EXCEPTION_NAMESPACE::GenericException<subtype>   \
{                                                                    \
public:                                                              \
    name() :                                                         \
        GenericException<subtype>(text)                              \
    {}                                                               \
                                                                     \
    name(const std::string& description) :                           \
        GenericException<subtype>(text ": " + description)           \
    {}                                                               \
}

NAMESPACE_END

#endif
