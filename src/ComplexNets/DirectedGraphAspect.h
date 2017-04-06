#pragma once

namespace graphpp
{
template <class Vertex, class T>
class DirectedGraphAspect : public T
{
public:
    DirectedGraphAspect(const bool isMultigraph = false) : T(true, isMultigraph){};

    /**
     * Method: removeVertex
     * -----------------
     * Description: Removes a vertex and all of its edge of the graph
     * @param v Vertex to be removed
     */
    void removeVertex(Vertex* v)
    {
        T::template removeVertex<Vertex>(v);

        auto it = v->inNeighborsIterator();

        while (!it.end())
        {
            Vertex* inNeighbor = *it;
            removeEdge(inNeighbor, v);
            it++;
        }

        it = v->outNeighborsIterator();

        while (!it.end())
        {
            Vertex* outNeighbor = *it;
            removeEdge(v, outNeighbor);
            it++;
        }
    }
};
}
