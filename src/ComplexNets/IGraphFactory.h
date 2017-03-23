#pragma once

#include "IBetweenness.h"
#include "IClusteringCoefficient.h"
#include "IDegreeDistribution.h"
#include "IGraphReader.h"
#include "INearestNeighborsDegree.h"
#include "IShellIndex.h"
#include "MaxClique.h"
#include "StrengthDistribution.h"

namespace graphpp
{
template <class Graph, class Vertex>
class IGraphFactory
{
public:
    virtual IBetweenness<Graph, Vertex>* createBetweenness(Graph& g) = 0;

    virtual IClusteringCoefficient<Graph, Vertex>* createClusteringCoefficient() = 0;

    virtual INearestNeighborsDegree<Graph, Vertex>* createNearestNeighborsDegree() = 0;

    virtual IShellIndex<Graph, Vertex>* createShellIndex(Graph& g) = 0;

    virtual IGraphReader<Graph, Vertex>* createGraphReader() = 0;

    virtual IDegreeDistribution<Graph, Vertex>* createDegreeDistribution(Graph& g) = 0;

    virtual StrengthDistribution<Graph, Vertex>* createStrengthDistribution(Graph& g) = 0;

    virtual MaxClique<Graph, Vertex>* createMaxClique(Graph& g) = 0;

    virtual MaxCliqueExact<Graph, Vertex>* createExactMaxClique(Graph& g, int max_time) = 0;

    virtual ~IGraphFactory()
    {
    }
};
}
