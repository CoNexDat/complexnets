#pragma once

#include "mili/mili.h"

namespace graphpp
{
template <class Graph, class Vertex>
class IDegreeDistribution
{
public:
    typedef std::map<typename Vertex::Degree, unsigned int> DistributionContainer;
    typedef CAutonomousIterator<DistributionContainer> DistributionIterator;

    virtual DistributionIterator iterator() = 0;

    virtual ~IDegreeDistribution() {}
};
}  // namespace graphpp
