#ifndef TRAVERSER_ORDERED_H
#define TRAVERSER_ORDERED_H

// AutonomousIterator<std::set<graphpp::AdjacencyListVertex*,graphpp::VertexComparator<graphpp::AdjacencyListVertex>,std::allocator<graphpp::AdjacencyListVertex*>>
// >
// CAutonomousIterator<std::set<graphpp::AdjacencyListVertex*,graphpp::VertexComparator<graphpp::AdjacencyListVertex>,std::allocator<graphpp::AdjacencyListVertex*>>
// >

#include <list>
#include "ComplexNets/mili/mili.h"

namespace graphpp
{
template <class Graph, class Vertex, class Visitor, class Comparator>
class TraverserOrdered
{
public:
    typedef typename Graph::VerticesIterator VertexForwardIterator;
    typedef typename std::list<Vertex*> vertexList;
    typedef typename vertexList::iterator vertexListIterator;

    static void traverse(Graph& graph, Visitor& visitor, Comparator compare)
    {
        vertexList orderedVertexs;
        vertexListIterator orderedVertexsIterator;
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

    static void traverse(vertexList orderedVertexs, Visitor& visitor)
    {
        bool keepTraversing = true;
        vertexListIterator orderedVertexsIterator = orderedVertexs.begin();

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

#endif
