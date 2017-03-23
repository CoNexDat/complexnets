#pragma once

namespace graphpp
{
template <class Graph, class Vertex, class Visitor>
class TraverserForward
{
public:
    static void traverse(Graph& graph, Visitor& visitor)
    {
        traverse(graph.verticesIterator(), visitor);
    }

    static void traverse(typename Graph::VerticesIterator iterator, Visitor& visitor)
    {
        bool keepTraversing = true;

        while (!iterator.end() && keepTraversing)
        {
            Vertex* v = *iterator;
            keepTraversing = visitor.visitVertex(v);
            ++iterator;
        }
    }
};
}
