/*
bitwise_enums: A minimal library for doing type-safe bitwise operations.
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
*/

#ifndef BITWISE_ENUMS_H
#define BITWISE_ENUMS_H

NAMESPACE_BEGIN

template <class Enum>
class bitwise_enum
{
    unsigned long int _value;
public:
    typedef unsigned int Bits;

    // CONSTRUCTORS:
    bitwise_enum(Enum init_value)
        : _value(init_value)
    {}

    bitwise_enum()
        : _value(0)
    {}

    bitwise_enum(const bitwise_enum<Enum>& other)
        : _value(other._value)
    {}

    // UNARY OPERATIONS:
    bitwise_enum<Enum> operator ~() const
    {
        return bitwise_enum<Enum>(~_value);
    }


    unsigned long int value() const
    {
        return _value;
    }

    bitwise_enum<Enum>& self_revert()
    {
        _value = ~_value;
        return *this;
    }

    bitwise_enum<Enum>& clear()
    {
        _value = 0;
        return *this;
    }

    // OPERATIONS with integrals:

    unsigned long int operator >> (Bits bits) const
    {
        return _value >> bits;
    }

    unsigned long int operator << (Bits bits) const
    {
        return _value << bits;
    }

    // OPERATIONS BETWEEN bitwise_enums:
    bitwise_enum<Enum>& operator |= (const bitwise_enum<Enum>& other)
    {
        _value |= other._value;
        return *this;
    }

    bitwise_enum<Enum>& operator &= (const bitwise_enum<Enum>& other)
    {
        _value &= other._value;
        return *this;
    }

    bitwise_enum<Enum>& operator ^= (const bitwise_enum<Enum>& other)
    {
        _value ^= other._value;
        return *this;
    }

    bitwise_enum<Enum> operator | (const bitwise_enum<Enum>& other) const
    {
        bitwise_enum<Enum> ret(*this);
        return (ret |= other);
    }

    bitwise_enum<Enum> operator & (const bitwise_enum<Enum>& other) const
    {
        bitwise_enum<Enum> ret(*this);
        return (ret &= other);
    }

    bitwise_enum<Enum> operator ^(const bitwise_enum<Enum>& other) const
    {
        bitwise_enum<Enum> ret(*this);
        return (ret ^= other);
    }

    bitwise_enum<Enum>& operator = (const bitwise_enum<Enum>& other)
    {
        _value = other._value;
        return *this;
    }

    bool operator == (const bitwise_enum<Enum>& other) const
    {
        return _value == other._value;
    }

    bool operator != (const bitwise_enum<Enum>& other) const
    {
        return ! operator==(other);
    }

    // utilities
    bool has_bits() const
    {
        return _value != 0;
    }

    bool has_bits(const bitwise_enum<Enum>& other) const
    {
        return (operator&(other)).has_bits();
    }

    unsigned int bits_count() const
    {
        unsigned long int v(_value);
        unsigned int result(0);

        while (v > 0)
        {
            result++;
            v &= v - 1;
        }

        return result;
    }
};


//Nonmember operators:
template <class Enum>
inline bitwise_enum<Enum> operator | (Enum value, const bitwise_enum<Enum>& e)
{
    return e | value;
}

template <class Enum>
inline bitwise_enum<Enum> operator & (Enum value, const bitwise_enum<Enum>& e)
{
    return e & value;
}

template <class Enum>
inline bitwise_enum<Enum> operator ^(Enum value, const bitwise_enum<Enum>& e)
{
    return e ^ value;
}


template <class Enum>
inline bitwise_enum<Enum> operator | (Enum a, Enum b)
{
    return bitwise_enum<Enum>(a) | bitwise_enum<Enum>(b);
}

template <class Enum>
inline bitwise_enum<Enum> operator & (Enum a, Enum b)
{
    return bitwise_enum<Enum>(a) & bitwise_enum<Enum>(b);
}

template <class Enum>
inline bitwise_enum<Enum> operator ^(Enum a, Enum b)
{
    return bitwise_enum<Enum>(a) ^ bitwise_enum<Enum>(b);
}

NAMESPACE_END

#endif
