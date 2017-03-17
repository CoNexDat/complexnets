#ifndef INTEGER_DISTRIBUTION_H
#define INTEGER_DISTRIBUTION_H

#include <stdio.h>
#include "TraverserForward.h"
#include "mili/mili.h"

namespace graphpp
{
template <class Graph, class Vertex, class Map>
class IntegerDistribution;

template <class Graph, class Vertex, class Map>
class IntegerDistributionVisitor
{
public:
    IntegerDistributionVisitor(IntegerDistribution<Graph, Vertex, Map>& observer)
        : integerDistributionObserver(observer)
    {
    }

    bool visitVertex(Vertex* vertex)
    {
        integerDistributionObserver.notify(vertex);
        return true;
    }

private:
    IntegerDistribution<Graph, Vertex, Map>& integerDistributionObserver;
};

typedef std::map<int, unsigned int> DistributionContainer;
typedef CAutonomousIterator<DistributionContainer> DistributionIterator;

template <class Graph, class Vertex, class Map>
class IntegerDistribution
{
public:
    DistributionIterator iterator() const
    {
        return DistributionIterator(distribution);
    }

    void notify(Vertex* vertex)
    {
        int d = map->get(vertex);
        if (distribution.count(d) != 0)
            distribution[d]++;
        else
            distribution[d] = 1;
    }

    void calculateDistribution(Graph& graph, Map* maper)
    {
        map = maper;
        IntegerDistributionVisitor<Graph, Vertex, Map> visitor(*this);
        TraverserForward<Graph, Vertex, IntegerDistributionVisitor<Graph, Vertex, Map>>::traverse(
            graph, visitor);
    }

private:
    Map* map;

    DistributionContainer distribution;
};
}

#endif
