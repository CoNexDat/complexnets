#ifndef PROPERTY_MAP_H
#define PROPERTY_MAP_H

#include <string>
#include <map>

namespace graphpp
{

class PropertyMap
{
public:
    typedef std::string PropertyName;
    typedef int VertexId;
    typedef std::map<PropertyName, VariantsSet> Properties;

    template <typename PropertyType>
    void addProperty(const PropertyName& name, VertexId id, PropertyType value)
    {
        if (properties.count(name) == 0)
        {
            VariantsSet set;
            set.insert(id, value);
            properties.insert(name, set);
        }
        else
        {
            properties.find(name).insert(id, value);
        }
    }

    template <typename PropertyType>
    PropertyType getProperty(const PropertyName& name, VertexId id) const
    {
        return getPropertySet(name).find(id);
    }

    const VariantsSet& getPropertySet(const PropertyName& name) const
    {
        return properties.find(name);
    }

private:

    Properties properties;
};
}




#endif