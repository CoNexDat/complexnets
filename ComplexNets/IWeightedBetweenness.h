#pragma once

#include <list>
#include <queue>
#include <stack>
#include <vector>

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
