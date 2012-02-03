#ifndef TRAVERSER_H
#define TRAVERSER_H

#include <queue>
#include <iostream>

namespace graphpp
{

template <class Graph, class Vertex, class Visitor>
class TraverserBFS
{
public:

    typedef typename Graph::VerticesConstIterator VertexForwardIterator;
    typedef typename Vertex::VerticesIterator NeighborsIterator;

    static void traverse(Graph& graph, Visitor& v)
    {
        VertexForwardIterator iter = graph.verticesIterator();

        if (iter.end()) return;

        Vertex* source = *iter;
        TraverseBFS(source, v);
    }

    static void traverse(Vertex* source, Visitor& v)
    {
        bool keepTraversing = true;

        std::queue<Vertex*> queue;
        queue.push(&source);

        int i = 0;
        while (!queue.empty() && keepTraversing)
        {
            Vertex* vertex = queue.front();
            queue.pop();
            vertex->setVisited(true);

            keepTraversing = v.visitVertex(vertex);

            if (keepTraversing)
            {
                NeighborsIterator it = vertex->neighborsIterator();

                while (!it.end())
                {
                    Vertex* neighbour = *it;

                    if (!neighbour.getVisited())
                    {
                        queue.push(neighbour);
                    }
                    it++;
                }
            }
        }
    }

};
}

#endif
