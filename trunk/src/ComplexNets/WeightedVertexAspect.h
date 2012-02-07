#ifndef WEIGHTED_VERTEX_ASPECT_H
#define WEIGHTED_VERTEX_ASPECT_H

#include <map>
#include "AdjacencyListVertex.h"

namespace graphpp
{
template <class T>
class WeightedVertexAspect : public T
{
protected:
    //TODO: make these typedefs private
    typedef AdjacencyListVertex::VertexId VertexId;
    typedef double Weight;
    typedef std::map<VertexId, Weight> NeighborsWeights;
    typedef AutonomousIterator<NeighborsWeights> WeightsIterator;

public:

    WeightedVertexAspect(VertexId id) : T(id) { }

    void addEdge(WeightedVertexAspect<T>* other, Weight weight)
    {
        T::addEdge(other);
        weights.insert(std::pair<VertexId, Weight>(other->getVertexId(), weight));
    }

    Weight edgeWeight(WeightedVertexAspect<T>* neighbour) const
    {
        return weights[neighbour->getVertexId()];
    }

    WeightsIterator weightsIterator()
    {
        WeightsIterator iter(weights);
        return iter;
    }

    Weight strength() const
    {
        WeightsIterator iter(weights);
        Weight str = 0.0;

        while (!iter.end())
            str += iter->second;

        return str;
    }

private:

    NeighborsWeights weights;
};
}

#endif
