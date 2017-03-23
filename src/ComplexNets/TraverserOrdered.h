#pragma once

#include <list>
#include "ComplexNets/mili/mili.h"

namespace graphpp
{
template <class Graph, class Vertex, class Visitor, class Comparator>
class TraverserOrdered
{
public:
    typedef typename Graph::VerticesIterator VertexForwardIterator;
    typedef typename std::list<Vertex*> VertexList;
    typedef typename VertexList::iterator VertexListIterator;

    static void traverse(Graph& graph, Visitor& visitor, Comparator compare)
    {
        VertexList orderedVertexs;
        VertexListIterator orderedVertexsIterator;
        VertexForwardIterator graphIterator = graph.verticesIterator();

        while (!graphIterator.end())
        {
            Vertex* v = *graphIterator;
            orderedVertexsIterator = orderedVertexs.begin();
            while ((orderedVertexsIterator != orderedVertexs.end()) &&
                   compare(v, (*orderedVertexsIterator)))
            {
                orderedVertexsIterator++;
            }
            v->setVisited(false);
            orderedVertexs.insert(orderedVertexsIterator, v);

            graphIterator++;
        }

        traverse(orderedVertexs, visitor);
    }

    static void traverse(VertexList orderedVertexs, Visitor& visitor)
    {
        bool keepTraversing = true;
        VertexListIterator orderedVertexsIterator = orderedVertexs.begin();

        while ((orderedVertexsIterator != orderedVertexs.end()) && keepTraversing)
        {
            Vertex* v = *orderedVertexsIterator;
            keepTraversing = visitor.visitVertex(v);
            ++orderedVertexsIterator;
            v->setVisited(true);
        }
    }
};
}
