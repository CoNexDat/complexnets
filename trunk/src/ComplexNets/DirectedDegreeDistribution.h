#ifndef DIRECTED_DEGREE_DISTRIBUTION_H
#define DIRECTED_DEGREE_DISTRIBUTION_H

#include <map>

#include "mili/mili.h"
#include "TraverserForward.h"
#include <stdio.h>
#include "DirectedVertexAspect.h"

namespace graphpp
{
/**
* Forward declaration of DirectedDegreeDistribution class
* @see DirectedDegreeDistribution below
*/
template <class Graph, class Vertex>
class DirectedDegreeDistribution;

/**
* Class: DirectedDegreeDistributionVisitor
* --------------------------------
* Description: Visitor used to traverse the vertices, which collects de degrees and notifies
* the DirectedDegreeDistribution class the data it gathers
* Template Argument Graph: Graph type
* Template Argument Vertex: Vertex type
*/
template <class Graph, class Vertex>
class DirectedDegreeDistributionVisitor
{
public:

    DirectedDegreeDistributionVisitor(DirectedDegreeDistribution<Graph, Vertex>& observer)
        : degreeDistributionObserver(observer) {}

    /**
    * Method: visitVertex
    * -------------------
    * Description: Action invoked by Traverser when a node is reached. The goal of
    * the visitVertex method is to notify the DirectedDegreeDistribution class about degrees/
    * @returns true if iterator should keep traversing
    */
    bool visitVertex(Vertex* vertex)
    {
        degreeDistributionObserver.notifyInDegree(vertex->inDegree());
		degreeDistributionObserver.notifyOutDegree(vertex->outDegree());
        return true;
    }

private:

    DirectedDegreeDistribution<Graph, Vertex>& degreeDistributionObserver;
};

template <class Graph, class Vertex>
class DirectedDegreeDistribution : public IDegreeDistribution<Graph, Vertex>
{
public:

    typedef std::map<typename Vertex::Degree, unsigned int> DistributionContainer;
    typedef CAutonomousIterator<DistributionContainer> DistributionIterator;

    DirectedDegreeDistribution(Graph& graph)
    {
        calculateDistribution(graph);
    }

    virtual DistributionIterator iterator() {
		return DistributionIterator(inDegreeDistribution);
	}
    
    DistributionIterator inDegreeIterator() const
    {
        return DistributionIterator(inDegreeDistribution);
    }

    DistributionIterator outDegreeIterator() const
    {
        return DistributionIterator(outDegreeDistribution);
    }

    void notifyInDegree(typename Vertex::Degree d)
    {
        if (inDegreeDistribution.count(d) != 0)
            inDegreeDistribution[d]++;
        else
            inDegreeDistribution[d] = 1;
    }
    
    void notifyOutDegree(typename Vertex::Degree d)
    {
        if (outDegreeDistribution.count(d) != 0)
            outDegreeDistribution[d]++;
        else
            outDegreeDistribution[d] = 1;
    }

private:

    void calculateDistribution(Graph& graph)
    {
        DirectedDegreeDistributionVisitor<Graph, Vertex> visitor(*this);
        TraverserForward<Graph, Vertex, DirectedDegreeDistributionVisitor<Graph, Vertex> >::traverse(graph, visitor);
    }

    DistributionContainer inDegreeDistribution;
	DistributionContainer outDegreeDistribution;
};
}


#endif
