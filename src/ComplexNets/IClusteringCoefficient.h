#ifndef ICLUSTERING_COEFFICIENT_H
#define ICLUSTERING_COEFFICIENT_H

#include <vector>

namespace graphpp
{

using namespace std;

template<class Graph, class Vertex>
class IClusteringCoefficient
{
public:
    typedef double Coefficient;
    typedef typename Vertex::Degree Degree;
    virtual Coefficient clusteringCoefficient(Graph& g, Degree d) = 0;
    virtual Coefficient vertexClusteringCoefficient(Vertex* vertex) = 0;

    class Boxplotentry 
    {
        public:
            std::vector<double> clusteringCoefs;
            int degree;
            double mean;
            double min;
            double max;
            double Q1;
            double Q2;
            double Q3;
            unsigned int bin;

           	bool operator<(const Boxplotentry& other) const
			   {
			      return degree < other.degree;
			   }

    };
};
}
#endif
