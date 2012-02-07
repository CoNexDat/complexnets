#ifndef DEGREE_DISTRIBUTION_H
#define DEGREE_DISTRIBUTION_H

#include <map>
#include "mili/mili.h"

namespace graphpp
{
template <class Graph, class Vertex>
class DegreeDistributionVisitor
{
public:

    DegreeDistributionVisitor(DegreeDistribution<Graph, Vertex>& observer)
        : degreeDistributionObserver(observer) {}

    bool visitVertex(Vertex* vertex)
    {
        degreeDistributionObserver.notifyDegree(vertex.degree());
    }

private:

    DegreeDistribution<Graph, Vertex>& degreeDistributionObserver;
};

template <class Graph, class Vertex>
class DegreeDistribution
{
public:

    typedef std::map<Vertex::Degree, unsigned int> DistributionContainer;
    typedef CAutonomousIterator<DistributionContainer> DistributionIterator;

    DegreeDistribution(Graph& graph)
    {
        calculateDistribution(graph);
    }

    DistributionIterator distributionIterator() const
    {
        return DistributionIterator(distribution);
    }

protected:

    void notifyDegree(Vertex::Degree d)
    {
        if (distribution.count(d) != 0)
            distribution[d]++;
        else
            distribution[d] = 1;
    }

private:

    void calculateDistribution(Graph& graph) const
    {
        DegreeDistributionVisitor visitor;
        TraverserForward<Graph, Vertex, DegreeDistributionVisitor>::traverse(graph, visitor);
    }

    DistributionContainer distribution;
}
}


#endif
