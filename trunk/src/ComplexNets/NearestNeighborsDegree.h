#ifndef NEAREST_NEIGHBORS_DEGREE_H
#define NEAREST_NEIGHBORS_DEGREE_H

namespace graphpp
{
template <class Graph, class Vertex>
class NearestNeighborsDegree
{

public:

    typedef double MeanDegree;
    typedef typename Vertex::VerticesIterator NeighborsIterator;
    typedef typename Graph::VerticesIterator VerticesIterator;

    static MeanDegree meanDegree(Graph& g, typename Vertex::Degree d)
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

        return meanDegreeSums / count;
    }

    static MeanDegree meanDegreeForVertex(Vertex* v)
    {
        NeighborsIterator it = v->neighborsIterator();
        typename Vertex::Degree degreeSum = 0;

        while (!it.end())
        {
            Vertex* n = *it;

            degreeSum += n->degree();

            ++it;
        }

        return MeanDegree(degreeSum) / MeanDegree(v->degree());
    }
};
}


#endif