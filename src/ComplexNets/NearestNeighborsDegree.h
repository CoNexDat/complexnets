#ifndef NEAREST_NEIGHBORS_DEGREE_H
#define NEAREST_NEIGHBORS_DEGREE_H

#include "INearestNeighborsDegree.h"

namespace graphpp
{
template <class Graph, class Vertex>
class NearestNeighborsDegree : public INearestNeighborsDegree<Graph, Vertex>
{
public:
    typedef typename graphpp::INearestNeighborsDegree<Graph, Vertex>::MeanDegree MeanDegree;
    typedef typename Vertex::VerticesIterator NeighborsIterator;
    typedef typename Graph::VerticesIterator VerticesIterator;

    virtual MeanDegree meanDegree(Graph& g, typename Vertex::Degree d)
    {
        VerticesIterator it = g.verticesIterator();
        unsigned int count = 0;
        MeanDegree meanDegreeSums = 0.0;

        while (!it.end())
        {
            Vertex* v = *it;

            if (v->degree() == d)
            {
                count++;
                meanDegreeSums += meanDegreeForVertex(v);
            }

            ++it;
        }

        return count == 0 ? 0 : meanDegreeSums / count;
    }

    virtual MeanDegree meanDegreeForVertex(Vertex* v)
    {
        NeighborsIterator it = v->neighborsIterator();
        typename Vertex::Degree degreeSum = 0;

        while (!it.end())
        {
            Vertex* n = *it;

            degreeSum += n->degree();

            ++it;
        }

        return v->degree() == 0 ? 0 : MeanDegree(degreeSum) / MeanDegree(v->degree());
    }
};
}

#endif
