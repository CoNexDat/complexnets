#ifndef DIRECTED_GRAPH_ASPECT_H
#define DIRECTED_GRAPH_ASPECT_H

namespace graphpp
{
template <class Vertex, class T>
class DirectedGraphAspect : public T
{
public:
    typedef typename Vertex::VerticesIterator NeighborsIterator;

    DirectedGraphAspect(const bool isMultigraph = false) : T(true, isMultigraph){};

    /**
* Method: removeVertex
* -----------------
* Description: Removes a vertex and all of its edge of the graph
* @param v Vertex to be added
*/
    void removeVertex(Vertex* v)
    {
        T::template removeVertex<Vertex>(v);

        NeighborsIterator it = v->inNeighborsIterator();

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

#endif
