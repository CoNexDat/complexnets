#ifndef CLUSTERING_COEFFICIENT_H
#define CLUSTERING_COEFFICIENT_H

namespace graphpp
{
template <class Graph, class Vertex>
class ClusteringCoefficient
{
public:

    typedef double Coefficient;
    typedef typename Graph::VerticesIterator VerticesIterator;
    typedef typename Vertex::VerticesIterator NeighborsIterator;
    typedef typename Vertex::Degree Degree;

    static Coefficient clusteringCoefficient(Graph& g, Degree d)
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

        return clusteringCoefSums / count;
    }

    static Coefficient vertexClusteringCoefficient(Vertex* vertex)
    {
        Coefficient links = 0.0;
        NeighborsIterator it = vertex->neighborsIterator();

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

        return links / (vertex->degree() * (vertex->degree() - 1));

    }
};
}

#endif