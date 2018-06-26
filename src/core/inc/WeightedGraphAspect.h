#pragma once

namespace graphpp
{
template <class WeightedVertex, class T>
class WeightedGraphAspect : public T
{
public:
    typedef double Weight;

    WeightedGraphAspect(const bool isDigraph = false, const bool isMultigraph = false)
        : T(isDigraph, isMultigraph){};

    void addEdge(WeightedVertex* s, WeightedVertex* d, Weight weight)
    {
        if (!this->isMultigraph() && s->isNeighbourOf(d))
            throw DuplicateEdge();
        s->addEdge(d, weight);
        if (!this->isDigraph())
            d->addEdge(s, weight);
    }
};
}  // namespace graphpp
