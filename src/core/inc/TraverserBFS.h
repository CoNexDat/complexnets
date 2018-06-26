// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

#pragma once

#include <iostream>
#include <queue>

#include "typedefs.h"

namespace graphpp
{
template <class Graph, class Vertex, class Visitor>
class TraverserBFS
{
public:
    typedef typename Graph::VerticesConstIterator VertexForwardIterator;

    static void traverse(Graph& graph, Visitor& v)
    {
        auto iter = graph.verticesIterator();

        if (iter.end())
            return;

        Vertex* source = *iter;
        traverse(source, v);
    }

    static void traverse(Vertex* source, Visitor& v)
    {
        bool keepTraversing = true;

        std::queue<Vertex*> queue;
        queue.push(source);
        source->setVisited(true);

        while (!queue.empty() && keepTraversing)
        {
            Vertex* vertex = queue.front();
            queue.pop();

            // cout << vertex->getVertexId();
            // cout << '\n';
            keepTraversing = v.visitVertex(vertex);

            if (keepTraversing)
            {
                auto it = vertex->neighborsIterator();

                while (!it.end())
                {
                    Vertex* neighbour = *it;
                    if (!neighbour->getVisited())
                    {
                        queue.push(neighbour);
                        neighbour->setVisited(true);
                    }
                    it++;
                }
            }
        }
    }
};
}  // namespace graphpp
