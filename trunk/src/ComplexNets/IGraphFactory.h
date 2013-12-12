#ifndef IGRAPHFACTORY_H
#define IGRAPHFACTORY_H

#include "IBetweenness.h"
#include "IClusteringCoefficient.h"
#include "INearestNeighborsDegree.h"
#include "IShellIndex.h"
#include "IGraphReader.h"
#include "IDegreeDistribution.h"
namespace graphpp
{
template<class Graph, class Vertex>
class IGraphFactory
{
public:
    virtual IBetweenness<Graph, Vertex>* createBetweenness(Graph& g) = 0;

    virtual IClusteringCoefficient<Graph, Vertex>* createClusteringCoefficient() = 0;

    virtual INearestNeighborsDegree<Graph, Vertex>* createNearestNeighborsDegree() = 0;

    virtual IShellIndex<Graph, Vertex>* createShellIndex(Graph& g) = 0;

    virtual IGraphReader<Graph, Vertex>* createGraphReader() = 0;

    virtual IDegreeDistribution<Graph, Vertex>* createDegreeDistribution(Graph& g) = 0;
};
}

#endif
