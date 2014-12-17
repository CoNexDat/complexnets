#ifndef I_WEIGHTED_BETWEENNESS_H
#define I_WEIGHTED_BETWEENNESS_H

#include <stack>
#include <queue>
#include <vector>
#include <list>

#include "mili/mili.h"

namespace graphpp
{
template <class WeightedGraph, class WeightedVertex>
class IWeightedBetweenness
{
public:
    typedef std::map<typename WeightedVertex::VertexId, double> BetweennessContainer;
    typedef AutonomousIterator<BetweennessContainer> BetweennessIterator;
    virtual BetweennessIterator iterator() = 0;
};
}

#endif

