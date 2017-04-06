#pragma once

namespace graphpp
{
template <class Graph, class Vertex>
class INearestNeighborsDegree
{
public:
    typedef typename Vertex::Degree Degree;

    virtual double meanDegree(Graph& g, Degree d) = 0;
    virtual double meanDegreeForVertex(Vertex* vertex) = 0;

    virtual double meanDegree(Graph& g, Degree d, bool out, bool in)
    {
        return meanDegree(g, d);
    }

    virtual double meanDegreeForVertex(Vertex* vertex, bool out, bool in)
    {
        return meanDegreeForVertex(vertex);
    }

    virtual ~INearestNeighborsDegree()
    {
    }
};
}
