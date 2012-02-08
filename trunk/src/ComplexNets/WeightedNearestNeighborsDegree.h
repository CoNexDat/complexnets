#ifndef WEIGHTED_NEAREST_NEIGHBORS_DEGREE_H
#define WEIGHTED_NEAREST_NEIGHBORS_DEGREE_H

namespace graphpp
{
template <class Graph, class Vertex>
class WeightedNearestNeighborsDegree
{

public:

    typedef double MeanDegree;
    typedef typename Vertex::VerticesIterator NeighborsIterator;
    typedef typename Graph::VerticesIterator VerticesIterator;

    //TODO check if this method is implemented correctly
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
                ++count;
                meanDegreeSums += meanDegreeForVertex(v);
            }

            ++it;
        }

        return meanDegreeSums / count;
    }

    static MeanDegree meanDegreeForVertex(Vertex* v)
    {
        NeighborsIterator it = v->neighborsIterator();
        typename Vertex::Weight degreeSum = 0.0;
        typename Vertex::Weight weigth;
        while (!it.end())
        {
            Vertex* n = static_cast<Vertex*>(*it);

            degreeSum += n->degree() * v->edgeWeight(n);

            ++it;
        }

        return MeanDegree(degreeSum) / MeanDegree(v->strength());
    }
};
}


#endif
