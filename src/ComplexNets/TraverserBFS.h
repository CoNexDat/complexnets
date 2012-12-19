// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

#ifndef TRAVERSER_H
#define TRAVERSER_H

#include <queue>
#include <iostream>

#include "../ComplexNets/typedefs.h"

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

			//cout << vertex->getVertexId();
			//cout << '\n';
            keepTraversing = v.visitVertex(vertex);

            if (keepTraversing)
            {
                NeighborsIterator it = vertex->neighborsIterator();

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
}

#endif
