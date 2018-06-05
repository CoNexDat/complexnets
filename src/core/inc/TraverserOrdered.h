#pragma once

#include <list>
#include "mili/mili.h"

namespace graphpp
{
template <class Graph, class Vertex, class Visitor, class Comparator>
class TraverserOrdered
{
public:
    typedef typename Graph::VerticesIterator VertexForwardIterator;
    typedef typename std::list<Vertex*> VertexList;
    typedef typename VertexList::iterator VertexListIterator;

    /**
     * Visit the vertexes in the graph in the order specified by the comparator in a decreasing
     * order. All the vertexes may not be visited if the visitor decides it in the current vertex
     * visit.
     * @param graph         the graph with the vertexes to traverse
     * @param visitor       the vertexes visitor
     * @param comparator    defines the order in which the vertexes will be visited
     */
    static void traverse(Graph& graph, Visitor& visitor, Comparator comparator)
    {
        VertexList orderedVertexes;
        VertexForwardIterator vertexesIt = graph.verticesIterator();
        while (!vertexesIt.end())
        {
            Vertex* v = *vertexesIt;
            VertexListIterator orderedVertexesIt = orderedVertexes.begin();
            while ((orderedVertexesIt != orderedVertexes.end()) &&
                   comparator(v, (*orderedVertexesIt)))
            {
                orderedVertexesIt++;
            }
            v->setVisited(false);
            orderedVertexes.insert(orderedVertexesIt, v);

            vertexesIt++;
        }

        traverse(orderedVertexes, visitor);
    }

    /**
     * Visit the vertexes in the order in which they are in the list.
     * All the vertexes may not be visited if the visitor decides it
     * in the current vertex visit.
     * @param orderedVertexes   the vertexes to visit
     * @param visitor           visits the vertexes
     */
    static void traverse(VertexList orderedVertexes, Visitor& visitor)
    {
        bool keepTraversing = true;
        VertexListIterator orderedVertexesIt = orderedVertexes.begin();

        while ((orderedVertexesIt != orderedVertexes.end()) && keepTraversing)
        {
            Vertex* v = *orderedVertexesIt;
            keepTraversing = visitor.visitVertex(v);
            v->setVisited(true);
            orderedVertexesIt++;
        }
    }
};
}  // namespace graphpp
