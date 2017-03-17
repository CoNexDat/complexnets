#ifndef PROPERTY_MAP_H
#define PROPERTY_MAP_H

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
        if (properties.count(name) == 0)
        {
            VariantsSet set;
            set.insert<PropertyType>(id, value);
            properties.insert(std::pair<PropertyName, VariantsSet>(name, set));
            // properties.insert(name, set);
        }
        else
        {
            properties.find(name)->second.insert<PropertyType>(id, value);
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
        return containsPropertySet(name) && getPropertySet(name).contains(id);
    }

    void clear()
    {
        properties.clear();
    }

private:
    Properties properties;
};
}

#endif
