#pragma once

#include "AdjacencyListVertex.h"

namespace graphpp
{
template <class T>
class WeightedVertexAspect : public T
{
public:
    // TODO: make these typedefs private
    typedef AdjacencyListVertex::VertexId VertexId;
    typedef double Weight;
    typedef std::map<VertexId, Weight> NeighborsWeights;
    typedef AutonomousIterator<NeighborsWeights> WeightsIterator;
    double distance;

    WeightedVertexAspect(VertexId id) : T(id) {}

    void addEdge(WeightedVertexAspect<T>* other, Weight weight)
    {
        T::template addEdge<WeightedVertexAspect<T>>(other);
        weights.insert(std::pair<VertexId, Weight>(other->getVertexId(), weight));
    }

    // TODO method should be const
    Weight edgeWeight(WeightedVertexAspect<T>* neighbour)
    {
        return weights[neighbour->getVertexId()];
    }

    WeightsIterator weightsIterator()
    {
        WeightsIterator iter(weights);
        return iter;
    }

    // TODO method should be const
    Weight strength()
    {
        WeightsIterator iter(weights);
        Weight str = 0.0;

        while (!iter.end())
        {
            str += iter->second;
            ++iter;
        }

        return str;
    }

private:
    NeighborsWeights weights;
};
}  // namespace graphpp
