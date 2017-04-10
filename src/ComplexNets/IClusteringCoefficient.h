#pragma once

#include <vector>

#include "Boxplotentry.h"
#include "mili/mili.h"

namespace graphpp
{
template <class Graph, class Vertex>
class IClusteringCoefficient
{
public:
    virtual double clusteringCoefficient(Graph& g, unsigned int d) = 0;
    virtual double vertexClusteringCoefficient(Vertex* vertex) = 0;

    virtual double vertexClusteringCoefficient(Vertex* vertex, bool, bool)
    {
        return vertexClusteringCoefficient(vertex);
    }

    virtual double clusteringCoefficient(Graph& g, unsigned int d, bool, bool)
    {
        return clusteringCoefficient(g, d);
    }

    virtual ~IClusteringCoefficient()
    {
    }
};
}
