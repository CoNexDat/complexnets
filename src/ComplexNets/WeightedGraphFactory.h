#pragma once

#include "IGraphFactory.h"
#include "WeightedBetweenness.h"
#include "WeightedClusteringCoefficient.h"
#include "WeightedNearestNeighborsDegree.h"
#include "Betweenness.h"
#include "IBetweenness.h"
#include "StrengthDistribution.h"
#include "WeightedGraphReader.h"

namespace graphpp
{
template <class Graph, class Vertex>
class WeightedGraphFactory : public IGraphFactory<Graph, Vertex>
{
public:
    virtual IGraphReader<Graph, Vertex>* createGraphReader()
    {
        return new WeightedGraphReader<Graph, Vertex>();
    }
    virtual IBetweenness<Graph, Vertex>* createBetweenness(Graph& g)
    {
        return new WeightedBetweenness<Graph, Vertex>(g);
    }
    virtual IClusteringCoefficient<Graph, Vertex>* createClusteringCoefficient()
    {
        return new WeightedClusteringCoefficient<Graph, Vertex>();
    }
    virtual INearestNeighborsDegree<Graph, Vertex>* createNearestNeighborsDegree()
    {
        return new WeightedNearestNeighborsDegree<Graph, Vertex>();
    }
    virtual IShellIndex<Graph, Vertex>* createShellIndex(Graph&)
    {
        // return new WeightedShellIndex<Graph,Vertex>();
        return nullptr;
    }
    virtual IDegreeDistribution<Graph, Vertex>* createDegreeDistribution(Graph& g)
    {
        return new DegreeDistribution<Graph, Vertex>(g);
    }

    virtual StrengthDistribution<Graph, Vertex>* createStrengthDistribution(Graph& g)
    {
        return new StrengthDistribution<Graph, Vertex>(g);
    }

    virtual MaxClique<Graph, Vertex>* createMaxClique(Graph&)
    {
        return nullptr;
    }

    virtual MaxCliqueExact<Graph, Vertex>* createExactMaxClique(Graph&, int)
    {
        return nullptr;
    }
};
}
