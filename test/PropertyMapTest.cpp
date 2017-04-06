#include <gtest/gtest.h>

#include "ComplexNets/PropertyMap.h"

namespace propertyMapTest
{

using namespace graphpp;
using namespace std;

TEST(PropertyMapTest, BasicTest)
{
    PropertyMap map;

    map.addProperty<int>("foo", "bar", 2);
    VariantsSet vset = map.getPropertySet("foo");
    ASSERT_EQ(vset.get_element<int>("bar"), 2);
    ASSERT_EQ(map.getProperty<int>("foo", "bar"), 2);

    ASSERT_TRUE(map.containsPropertySet("foo"));
    ASSERT_TRUE(map.containsProperty("foo", "bar"));

    map.clear();
    ASSERT_FALSE(map.containsPropertySet("foo"));
    ASSERT_FALSE(map.containsProperty("foo", "bar"));
}

}

