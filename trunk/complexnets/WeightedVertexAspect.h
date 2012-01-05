#ifndef WEIGHTED_VERTEX_ASPECT_H
#define WEIGHTED_VERTEX_ASPECT_H

#include <map>

namespace graphpp
{
    template <class T>
    class WeightedVertexAspect : public T
    {
    public:
        
        typedef double Weight;
        
        WeightedGraphAspect(VertexId id) : T(id) {}
        
        void addEdge(WeightedVertexAspect<T>* other, Weight weight)
        {
            T::addEdge(other);
        }
        
        Weight edgeWeight(WeightedVertexAspect<T>* neighbour) const
        {
            return weightsp[neighbour->getVertexId()];
        }
        
        Weight strength() const
        {
            WeightsIterator iter(weights);
            Weight str = 0.0;
            
            while(!iter.end())
                str += iter->second;

            return str;
        }
        
    private:
        
        typedef std::map<VertexId, Weight> NeighborsWeights;
        typedef AutonomousIterator<NeighborsWeights> WeightsIterator;
        
        NeighborsWeights weights;
    };
}

#endif
