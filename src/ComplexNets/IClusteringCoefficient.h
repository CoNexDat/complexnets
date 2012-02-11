#ifndef ICLUSTERING_COEFFICIENT_H
#define ICLUSTERING_COEFFICIENT_H

namespace graphpp
{
template<class Graph, class Vertex>
class IClusteringCoefficient
{
public:
    typedef double Coefficient;
    typedef typename Vertex::Degree Degree;
    static Coefficient clusteringCoefficient(Graph& g, Degree d);
    static Coefficient vertexClusteringCoefficient(Vertex* vertex);
};
}
#endif
