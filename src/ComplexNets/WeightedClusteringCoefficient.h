#ifndef WEIGHTEDCLUSTERINGCOEFFICIENT_H
#define WEIGHTEDCLUSTERINGCOEFFICIENT_H

#include "IClusteringCoefficient.h"

namespace graphpp
{
template <class Graph, class Vertex>
class WeightedClusteringCoefficient : public IClusteringCoefficient<Graph, Vertex>
{
public:
    typedef typename graphpp::IClusteringCoefficient<Graph, Vertex>::Coefficient Coefficient;
    typedef typename Graph::VerticesIterator VerticesIterator;
    typedef typename Vertex::VerticesIterator NeighborsIterator;
    typedef typename IClusteringCoefficient<Graph, Vertex>::Degree Degree;

    //TODO check if this method is implemented correctly
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
                ++count;
                clusteringCoefSums += vertexClusteringCoefficient(v);
            }

            ++it;
        }

        return clusteringCoefSums / count;
    }

    virtual Coefficient vertexClusteringCoefficient(Vertex* vertex)
    {
        Coefficient links = 0.0;
        NeighborsIterator it = vertex->neighborsIterator();

        while (!it.end())
        {
            Vertex* n = static_cast<Vertex*>(*it);

            NeighborsIterator innerIter = n->neighborsIterator();

            while (!innerIter.end())
            {
                Vertex* i = static_cast<Vertex*>(*innerIter);
                //if i is neighbour of vertex, we close a triangle
                if (i->isNeighbourOf(vertex))
                    links += (vertex->edgeWeight(n) + i->edgeWeight(vertex)) / 2.0;

                ++innerIter;
            }
            ++it;
        }

        return links / (vertex->strength() * (vertex->degree() - 1));

    }
};
}

#endif
