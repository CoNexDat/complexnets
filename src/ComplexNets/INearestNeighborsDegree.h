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
    static MeanDegree meanDegree(Graph& g, Degree d);
    static MeanDegree meanDegreeForVertex(Graph& g);
};
}

#endif
