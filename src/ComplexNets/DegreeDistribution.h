#ifndef DEGREE_DISTRIBUTION_H
#define DEGREE_DISTRIBUTION_H

#include <map>

#include "mili/mili.h"
#include "TraverserForward.h"

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
        : degreeDistributionObserver(observer) {}

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
class DegreeDistribution
{
public:

    typedef std::map<typename Vertex::Degree, unsigned int> DistributionContainer;
    typedef CAutonomousIterator<DistributionContainer> DistributionIterator;

    DegreeDistribution(Graph& graph)
    {
        calculateDistribution(graph);
    }

    DistributionIterator iterator() const
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
        TraverserForward<Graph, Vertex, DegreeDistributionVisitor<Graph, Vertex> >::traverse(graph, visitor);
    }

    DistributionContainer distribution;
};
}


#endif
