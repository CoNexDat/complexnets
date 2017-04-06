#pragma once

#include <vector>

#include "mili/mili.h"

namespace graphpp
{
template <class Graph, class Vertex>
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
        int degree;
        double mean;
        double min;
        double max;
        double Q1;
        double Q2;
        double Q3;
        unsigned int bin;
        std::vector<double> values;

        // define the operator to order vectors properly
        bool operator<(const Boxplotentry& other) const
        {
            return degree < other.degree;
        }

        std::string str() const
        {
            std::stringstream ss;

            ss << "Mean: " << mean << std::endl;
            ss << "Min: " << min << std::endl;
            ss << "Q1: " << Q1 << std::endl;
            ss << "Q2: " << Q2 << std::endl;
            ss << "Q3: " << Q3 << std::endl;
            ss << "Max: " << max << std::endl;

            return ss.str();
        }
    };

    virtual Coefficient vertexClusteringCoefficient(Vertex* vertex, bool out, bool in)
    {
        return vertexClusteringCoefficient(vertex);
    }

    virtual Coefficient clusteringCoefficient(Graph& g, Degree d, bool out, bool in)
    {
        return clusteringCoefficient(g, d);
    }

    virtual ~IClusteringCoefficient()
    {
    }
};
}
