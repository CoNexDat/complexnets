#pragma once

#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "mili/mili.h"

namespace graphpp
{
template <class Graph, class Vertex>
class IBetweenness
{
public:
    typedef std::map<typename Vertex::VertexId, double> BetweennessContainer;
    typedef AutonomousIterator<BetweennessContainer> BetweennessIterator;
    virtual BetweennessIterator iterator() = 0;

    virtual ~IBetweenness()
    {
    }
};
}
