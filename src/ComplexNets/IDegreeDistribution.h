#ifndef IDEGREE_DISTRIBUTION_H
#define IDEGREE_DISTRIBUTION_H

#include "ComplexNets/mili/mili.h"

namespace graphpp
{
template <class Graph, class Vertex>
class IDegreeDistribution
{
public:
    typedef std::map<typename Vertex::Degree, unsigned int> DistributionContainer;
    typedef CAutonomousIterator<DistributionContainer> DistributionIterator;

    virtual DistributionIterator iterator() = 0;
};
}

#endif
