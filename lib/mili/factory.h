/*
factory: A minimal library for a generic factory.
    Copyright (C) 2009  Daniel Gutson and Marcelo Caro, FuDePAN

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

#ifndef FACTORY_H
#define FACTORY_H

#include <map>
#include "delete_container.h"

NAMESPACE_BEGIN

template < class Key, class Base, class ConstructorParameterType = void >
class Factory
{
    struct Creator
    {
        virtual Base* create(ConstructorParameterType p) const = 0;
        virtual ~Creator() {}
    };

    std::map<Key, Creator*> _creators;

public:
    template <class DerivedClass>
    void register_factory(const Key& key)
    {
        class ConcreteCreator : public Creator
        {
            virtual Base* create(ConstructorParameterType p) const
            {
                return new DerivedClass(p);
            }
        };

        _creators[key] = new ConcreteCreator;
    }

    Base* new_class(const Key& key, ConstructorParameterType p) const
    {
        typename std::map<Key, Creator*>::const_iterator it = _creators.find(key);

        if (it != _creators.end())
            return it->second->create(p);
        else
            return NULL;
    }

    ~Factory()
    {
        delete_container(_creators);
    }
};

template <class Key, class Base>
class Factory<Key, Base, void>
{
    struct Creator
    {
        virtual Base* create() const = 0;
        virtual ~Creator() {}
    };

    std::map<Key, Creator*> _creators;

public:
    template <class DerivedClass>
    void register_factory(const Key& key)
    {
        class ConcreteCreator : public Creator
        {
            virtual Base* create() const
            {
                return new DerivedClass;
            }
        };

        _creators[key] = new ConcreteCreator;
    }

    Base* new_class(const Key& key) const
    {
        typename std::map<Key, Creator*>::const_iterator it = _creators.find(key);

        if (it != _creators.end())
            return it->second->create();
        else
            return NULL;
    }

    ~Factory()
    {
        delete_container(_creators);
    }
};

NAMESPACE_END

#endif
