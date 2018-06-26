#pragma once

#include <sstream> // Required to avoid compilation issue with ctype_base library.
#include "mili/mili.h"

namespace graphpp
{
class PropertyMap
{
public:
    typedef std::string PropertyName;
    typedef std::string Id;
    typedef std::map<PropertyName, VariantsSet> Properties;

    template <typename PropertyType>
    void addProperty(const PropertyName& name, Id id, PropertyType value)
    {
        auto search = properties.find(name);

        if (search == properties.end())
        {
            VariantsSet set;
            set.insert<PropertyType>(id, value);
            properties.insert(std::pair<PropertyName, VariantsSet>(name, set));
            // properties.insert(name, set);
        }
        else
        {
            search->second.insert<PropertyType>(id, value);
        }
    }

    // TODO method should be const
    template <typename PropertyType>
    PropertyType getProperty(const PropertyName& name, const Id id)
    {
        return getPropertySet(name).get_element<PropertyType>(id);
    }

    // TODO method should be const
    // FIXME this method causes segmentation fault when property name does not exists on map!!
    VariantsSet& getPropertySet(const PropertyName& name)
    {
        return properties.find(name)->second;
    }

    bool containsPropertySet(const PropertyName& name) const
    {
        return properties.count(name) > 0;
    }

    // TODO method should be const
    bool containsProperty(const PropertyName& name, const Id id)
    {
        auto search = properties.find(name);
        if (search == properties.end())
            return false;
        return search->second.contains(id);
    }

    void clear()
    {
        properties.clear();
    }

private:
    Properties properties;
};
}  // namespace graphpp
