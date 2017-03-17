#pragma once

#include "IntegerDistribution.h"
#include "mili/mili.h"

namespace graphpp
{
template <class Graph, class Vertex>
class IMaxClique
{
public:
    virtual DistributionIterator distIterator() = 0;
    virtual std::list<int> getMaxCliqueList() = 0;
    virtual bool finished() = 0;

    virtual ~IMaxClique()
    {
    }
};
}
