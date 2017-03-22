#ifndef INEAREST_NEIGHBORS_DEGREE_H
#define INEAREST_NEIGHBORS_DEGREE_H

namespace graphpp
{
template <class Graph, class Vertex>
class INearestNeighborsDegree
{
public:
    typedef typename Vertex::Degree Degree;
    typedef double MeanDegree;
    virtual MeanDegree meanDegree(Graph& g, Degree d) = 0;
    virtual MeanDegree meanDegreeForVertex(Vertex* vertex) = 0;

    virtual MeanDegree meanDegree(Graph& g, Degree d, bool out, bool in)
    {
        return meanDegree(g, d);
    }

    virtual MeanDegree meanDegreeForVertex(Vertex* vertex, bool out, bool in)
    {
        return meanDegreeForVertex(vertex);
    }

    virtual ~INearestNeighborsDegree()
    {
    }
};
}

#endif
