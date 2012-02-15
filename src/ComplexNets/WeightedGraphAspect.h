#ifndef WEIGHTED_GRAPH_ASPECT_H
#define WEIGHTED_GRAPH_ASPECT_H

namespace graphpp
{
template <class WeightedVertex, class T>
class WeightedGraphAspect : public T
{
public:

    typedef double Weight;

    WeightedGraphAspect(const bool isDigraph = true, const bool isMultigraph = true) : T(isDigraph,isMultigraph){};

    void addEdge(WeightedVertex* s, WeightedVertex* d, Weight weight)
    {
        s->addEdge(d, weight);
        d->addEdge(s, weight);
    }

};
}

#endif
