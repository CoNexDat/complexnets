#ifndef WEIGHTED_GRAPH_ASPECT_H
#define WEIGHTED_GRAPH_ASPECT_H

namespace graphpp
{
template <class WeightedVertex, class T>
class WeightedGraphAspect : public T
{
public:

    typedef double Weight;

    WeightedGraphAspect() {}
    ~WeightedGraphAspect()
    {
//TODO vertices should be freed.
    }

    void addEdge(WeightedVertex* s, WeightedVertex* d, Weight weight)
    {
        s->addEdge(d, weight);
        d->addEdge(s, weight);
    }

};
}

#endif
