#ifndef INEAREST_NEIGHBORS_DEGREE_H
#define INEAREST_NEIGHBORS_DEGREE_H

namespace graphpp
{
template<class Graph, class Vertex>
class INearestNeighborsDegree
{
public:
    typedef typename Vertex::Degree Degree;
    typedef double MeanDegree;
    virtual MeanDegree meanDegree(Graph& g, Degree d) = 0;
    virtual MeanDegree meanDegreeForVertex(Vertex* vertex) = 0;
};
}

#endif
