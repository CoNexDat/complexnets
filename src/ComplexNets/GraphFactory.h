#ifndef GRAPHFACTORY_H
#define GRAPHFACTORY_H

#include "IGraphFactory.h"
#include "Betweenness.h"
#include "ClusteringCoefficient.h"
#include "NearestNeighborsDegree.h"
#include "ShellIndex.h"
#include "GraphReader.h"
#include "DegreeDistribution.h"

namespace graphpp
{
template<class Graph, class Vertex>
class GraphFactory: public IGraphFactory<Graph, Vertex>
{
public:
    virtual IGraphReader<Graph, Vertex>* createGraphReader()
    {
        return new GraphReader<Graph, Vertex>();
    }
    virtual IBetweenness<Graph, Vertex>* createBetweenness(Graph& g)
    {
        return new Betweenness<Graph, Vertex>(g);
    }
    virtual MaxClique<Graph, Vertex>* createMaxClique(Graph& g)
    {
        return new MaxClique<Graph, Vertex>(g);
    }
    virtual MaxCliqueExact<Graph, Vertex>* createExactMaxClique(Graph& g, int max_time)
    {
        return new MaxCliqueExact<Graph, Vertex>(g, max_time);
    }
    virtual IClusteringCoefficient<Graph, Vertex>* createClusteringCoefficient()
    {
        return new ClusteringCoefficient<Graph, Vertex>();
    }
    virtual INearestNeighborsDegree<Graph, Vertex>* createNearestNeighborsDegree()
    {
        return new NearestNeighborsDegree<Graph, Vertex>();
    }
    virtual IShellIndex<Graph, Vertex>* createShellIndex(Graph& g)
    {
        return new ShellIndex<Graph, Vertex>(g);
    }

    virtual IDegreeDistribution<Graph, Vertex>* createDegreeDistribution(Graph& g)
    {
        return new DegreeDistribution<Graph, Vertex>(g);
    }

    virtual StrengthDistribution<Graph, Vertex>* createStrengthDistribution(Graph& g)
    {
        return NULL;
    }
};
}

#endif
