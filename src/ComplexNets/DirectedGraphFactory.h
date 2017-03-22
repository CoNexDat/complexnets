#ifndef DIRECTED_GRAPH_FACTORY_H
#define DIRECTED_GRAPH_FACTORY_H

#include "DirectedClusteringCoefficient.h"
#include "DirectedDegreeDistribution.h"
#include "DirectedNearestNeighborsDegree.h"
#include "GraphReader.h"
#include "IGraphFactory.h"

namespace graphpp
{
template <class Graph, class Vertex>
class DirectedGraphFactory : public IGraphFactory<Graph, Vertex>
{
public:
    virtual IGraphReader<Graph, Vertex>* createGraphReader()
    {
        return new GraphReader<Graph, Vertex>();
    }
    virtual IBetweenness<Graph, Vertex>* createBetweenness(Graph&)
    {
        // TODO Implement this
        // return new DirectedBetweenness<Graph,Vertex>();
        return nullptr;
    }
    virtual IClusteringCoefficient<Graph, Vertex>* createClusteringCoefficient()
    {
        return new DirectedClusteringCoefficient<Graph, Vertex>();
    }
    virtual INearestNeighborsDegree<Graph, Vertex>* createNearestNeighborsDegree()
    {
        return new DirectedNearestNeighborsDegree<Graph, Vertex>();
    }
    virtual IShellIndex<Graph, Vertex>* createShellIndex(Graph&)
    {
        // TODO Implement this
        // return new DirectedShellIndex<Graph,Vertex>();
        return nullptr;
    }
    virtual IDegreeDistribution<Graph, Vertex>* createDegreeDistribution(Graph& g)
    {
        return new DirectedDegreeDistribution<Graph, Vertex>(g);
    }

    virtual MaxClique<Graph, Vertex>* createMaxClique(Graph&)
    {
        return nullptr;
    }

    virtual MaxCliqueExact<Graph, Vertex>* createExactMaxClique(Graph&, int)
    {
        return nullptr;
    }

    virtual StrengthDistribution<Graph, Vertex>* createStrengthDistribution(Graph& g)
    {
        return nullptr;
    }
};
}

#endif
