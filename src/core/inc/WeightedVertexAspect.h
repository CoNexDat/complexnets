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
    typedef AdjacencyListVertex::VertexContainer VertexContainer;
    typedef AdjacencyListVertex::VerticesConstIterator VerticesConstIterator;
    typedef AdjacencyListVertex::VerticesIterator VerticesIterator;
    double distance;

    WeightedVertexAspect(VertexId id) : T(id) {
        neighborIds = new std::list<unsigned int>[200];
        neighboursWeight = new std::vector<double>(200);
    }

    void addEdge(WeightedVertexAspect<T>* other, Weight weight)
    {
        T::template addEdge<WeightedVertexAspect<T>>(other);
        myStrength += weight;
        weights.insert(std::pair<VertexId, Weight>(other->getVertexId(), weight));
        neighboursWeight-> push_back(weight);
        neighborIds->push_back(other->getVertexId());
    }

    // TODO method should be const
    Weight edgeWeight(WeightedVertexAspect<T>* neighbour)
    {
        return weights[neighbour->getVertexId()];
    }

    Weight edgeWeightByNeighbour(unsigned int neighbourId)
    {
        return weights[neighbourId];
    }

    Weight getNeighbourWeight(unsigned int neighbourId){
        int index = 0;
        for (unsigned int neigh : (*neighborIds)){
            if(neigh == neighbourId){
                return neighboursWeight->at(index);
            }
            index++;
        }
        return index;
    }

    WeightsIterator weightsIterator()
    {
        WeightsIterator iter(weights);
        return iter;
    }


    std::list<unsigned int> *getNeighborsIds(){
        return neighborIds;
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

    Weight getInitialStrength() {
        if(!strengthComputed){
            double currentStrength = 0.0;
            for(auto it = neighboursWeight->begin(); it != neighboursWeight->end(); ++it) {
                currentStrength += *it;
            }
            myStrength = currentStrength;
        }
        return myStrength ;
    }

private:
    double myStrength = 0.0;
    NeighborsWeights weights;
    std::list<unsigned int> * neighborIds;
    std::vector<double>* neighboursWeight;
    bool strengthComputed;
};
}  // namespace graphpp
