#ifndef DEGREE_DISTRIBUTION_H
#define DEGREE_DISTRIBUTION_H

#include <stdio.h>
#include "IDegreeDistribution.h"
#include "TraverserForward.h"
#include "mili/mili.h"

namespace graphpp
{
/**
* Forward declaration of DegreeDistribution class
* @see DegreeDistribution below
*/
template <class Graph, class Vertex>
class DegreeDistribution;

/**
* Class: DegreeDistributionVisitor
* --------------------------------
* Description: Visitor used to traverse the vertices, which collects de degrees and notifies
* the DegreeDistribution class the data it gathers
* Template Argument Graph: Graph type
* Template Argument Vertex: Vertex type
*/
template <class Graph, class Vertex>
class DegreeDistributionVisitor
{
public:
    DegreeDistributionVisitor(DegreeDistribution<Graph, Vertex>& observer)
        : degreeDistributionObserver(observer)
    {
    }

    /**
    * Method: visitVertex
    * -------------------
    * Description: Action invoked by Traverser when a node is reached. The goal of
    * the visitVertex method is to notify the DegreeDistribution class about degrees/
    * @returns true if iterator should keep traversing
    */
    bool visitVertex(Vertex* vertex)
    {
        degreeDistributionObserver.notifyDegree(vertex->degree());
        return true;
    }

private:
    DegreeDistribution<Graph, Vertex>& degreeDistributionObserver;
};

template <class Graph, class Vertex>
class DegreeDistribution : public IDegreeDistribution<Graph, Vertex>
{
public:
    typedef std::map<typename Vertex::Degree, unsigned int> DistributionContainer;
    typedef CAutonomousIterator<DistributionContainer> DistributionIterator;

    DegreeDistribution(Graph& graph)
    {
        calculateDistribution(graph);
    }

    virtual DistributionIterator iterator()
    {
        return DistributionIterator(distribution);
    }

    void notifyDegree(typename Vertex::Degree d)
    {
        if (distribution.count(d) != 0)
            distribution[d]++;
        else
            distribution[d] = 1;
    }

private:
    void calculateDistribution(Graph& graph)
    {
        DegreeDistributionVisitor<Graph, Vertex> visitor(*this);
        TraverserForward<Graph, Vertex, DegreeDistributionVisitor<Graph, Vertex>>::traverse(
            graph, visitor);
    }

    DistributionContainer distribution;
};
}

#endif
