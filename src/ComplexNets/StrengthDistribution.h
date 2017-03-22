#ifndef STRENGTH_DISTRIBUTION_H
#define STRENGTH_DISTRIBUTION_H

#include <stdio.h>
#include "TraverserForward.h"
#include "WeightedVertexAspect.h"
#include "mili/mili.h"

namespace graphpp
{
/**
* Forward declaration of StrengthDistribution class
* @see StrengthDistribution below
*/
template <class Graph, class Vertex>
class StrengthDistribution;

/**
* Class: StrengthDistributionVisitor
* --------------------------------
* Description: Visitor used to traverse the vertices, which collects de degrees and notifies
* the StrengthDistribution class the data it gathers
* Template Argument Graph: Graph type
* Template Argument Vertex: Vertex type
*/
template <class Graph, class Vertex>
class StrengthDistributionVisitor
{
public:
    StrengthDistributionVisitor(StrengthDistribution<Graph, Vertex>& observer)
        : strengthDistributionObserver(observer)
    {
    }

    /**
    * Method: visitVertex
    * -------------------
    * Description: Action invoked by Traverser when a node is reached. The goal of
    * the visitVertex method is to notify the StrengthDistribution class about degrees/
    * @returns true if iterator should keep traversing
    */
    bool visitVertex(Vertex* vertex)
    {
        strengthDistributionObserver.notifyDegree(vertex->strength());
        return true;
    }

private:
    StrengthDistribution<Graph, Vertex>& strengthDistributionObserver;
};

template <class Graph, class Vertex>
class StrengthDistribution
{
public:
    typedef std::map<typename Vertex::Weight, unsigned int> DistributionContainer;
    typedef CAutonomousIterator<DistributionContainer> DistributionIterator;

    StrengthDistribution(Graph& graph)
    {
        calculateDistribution(graph);
    }

    virtual DistributionIterator iterator()
    {
        return DistributionIterator(distribution);
    }

    void notifyDegree(typename Vertex::Weight d)
    {
        if (distribution.count(d) != 0)
            distribution[d]++;
        else
            distribution[d] = 1;
    }

    virtual ~StrengthDistribution()
    {
    }

private:
    void calculateDistribution(Graph& graph)
    {
        StrengthDistributionVisitor<Graph, Vertex> visitor(*this);
        TraverserForward<Graph, Vertex, StrengthDistributionVisitor<Graph, Vertex>>::traverse(
            graph, visitor);
    }

    DistributionContainer distribution;
};
}

#endif
