#ifndef CLUSTERING_COEFFICIENT_H
#define CLUSTERING_COEFFICIENT_H

#include "IClusteringCoefficient.h"

namespace graphpp
{

template <class Graph, class Vertex>
class ClusteringCoefficient : public IClusteringCoefficient<Graph, Vertex>
{
public:
    typedef typename graphpp::IClusteringCoefficient<Graph, Vertex>::Coefficient Coefficient;
    typedef typename Graph::VerticesIterator VerticesIterator;
    typedef typename Vertex::VerticesIterator NeighborsIterator;
    typedef typename IClusteringCoefficient<Graph, Vertex>::Degree Degree;

    virtual Coefficient clusteringCoefficient(Graph& g, Degree d)
    {
        VerticesIterator it = g.verticesIterator();
        unsigned int count = 0;
        Coefficient clusteringCoefSums = 0.0;

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

    virtual Coefficient vertexClusteringCoefficient(Vertex* vertex)
    {
        Coefficient links = 0.0;
        NeighborsIterator it = vertex->neighborsIterator();
        Coefficient ret;

        while (!it.end())
        {
            Vertex* n = *it;

            NeighborsIterator innerIter = n->neighborsIterator();

            while (!innerIter.end())
            {
                Vertex* i = *innerIter;
                //if i is neighbour of vertex, we close a triangle
                if (i->isNeighbourOf(vertex))
                {
                    links += 1.0;
                }

                ++innerIter;
            }

            ++it;
        }

        //This is to avoid division by cero
        if (vertex->degree() == 0 || vertex->degree() == 1)
            ret = 0;
        else
            ret = links / (vertex->degree() * (vertex->degree() - 1));

        return ret;

    }
};
}

#endif
