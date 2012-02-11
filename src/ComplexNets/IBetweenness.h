#ifndef IBETWEENNESS_H
#define IBETWEENNESS_H

#include <stack>
#include <queue>
#include <vector>
#include <list>

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
};
}

#endif
