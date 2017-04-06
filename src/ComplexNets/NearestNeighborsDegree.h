#pragma once

#include "INearestNeighborsDegree.h"

namespace graphpp
{
template <class Graph, class Vertex>
class NearestNeighborsDegree : public INearestNeighborsDegree<Graph, Vertex>
{
public:
    virtual double meanDegree(Graph& g, typename Vertex::Degree d)
    {
        auto it = g.verticesIterator();
        unsigned int count = 0;
        double meanDegreeSums = 0.0;

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

    virtual double meanDegreeForVertex(Vertex* v)
    {
        auto it = v->neighborsIterator();
        typename Vertex::Degree degreeSum = 0;

        while (!it.end())
        {
            Vertex* n = *it;

            degreeSum += n->degree();

            ++it;
        }

        return v->degree() == 0 ? 0 : double(degreeSum) / v->degree();
    }
};
}
