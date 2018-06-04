#pragma once

#include "IClusteringCoefficient.h"

namespace graphpp
{
template <class Graph, class Vertex>
class ClusteringCoefficient : public IClusteringCoefficient<Graph, Vertex>
{
public:
    virtual double clusteringCoefficient(Graph& g, unsigned int d)
    {
        auto it = g.verticesIterator();
        unsigned int count = 0;
        double clusteringCoefSums = 0.0;

        while (!it.end())
        {
            Vertex* v = *it;

            if (v->degree() == d)
            {
                count++;
                clusteringCoefSums += vertexClusteringCoefficient(v);
            }

            ++it;
        }

        return count == 0 ? 0 : clusteringCoefSums / count;
    }

    virtual double vertexClusteringCoefficient(Vertex* vertex)
    {
        double links = 0.0;
        auto it = vertex->neighborsIterator();
        double ret;

        while (!it.end())
        {
            Vertex* n = *it;

            auto innerIter = n->neighborsIterator();

            while (!innerIter.end())
            {
                Vertex* i = *innerIter;
                // if i is neighbour of vertex, we close a triangle
                if (i->isNeighbourOf(vertex))
                {
                    links += 1.0;
                }

                ++innerIter;
            }

            ++it;
        }

        // This is to avoid division by cero
        if (vertex->degree() == 0 || vertex->degree() == 1)
            ret = 0;
        else
            ret = links / (vertex->degree() * (vertex->degree() - 1));

        return ret;
    }
};
}  // namespace graphpp
