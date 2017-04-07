#pragma once

#include <vector>

namespace graphpp
{
class Boxplotentry
{
public:
    unsigned int degree;
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
}
