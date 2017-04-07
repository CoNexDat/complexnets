// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

#pragma once

#include <math.h>
#include <algorithm>
#include <vector>
#include "TraverserBFS.h"
#include "mili/mili.h"

namespace graphpp
{
template <class Graph, class Vertex>
class ConnectivityVisitor;

template <class Graph, class Vertex>
class ConnectivityVerifier
{
public:
    std::list<unsigned int> vertexesLeft;
    std::list<unsigned int> vertexesInComponent;

    ConnectivityVerifier()
    {
    }

    void visited(unsigned int id)
    {
        vertexesInComponent.push_back(id);
        vertexesLeft.remove(id);
    }

    void getBiggestComponent(Graph* graph)
    {
        auto it = graph->verticesConstIterator();
        while (!it.end())
        {
            vertexesLeft.push_back((*it)->getVertexId());
            ++it;
        }

        ConnectivityVisitor<Graph, Vertex> visitor(this);
        do
        {
            vertexesInComponent.clear();
            Vertex* source = graph->getVertexById(vertexesLeft.back());
            vertexesLeft.pop_back();
            TraverserBFS<Graph, Vertex, ConnectivityVisitor<Graph, Vertex>>::traverse(
                source, visitor);
        } while (!vertexesLeft.empty() && vertexesInComponent.size() < graph->verticesCount() / 2);

        auto it2 = graph->verticesConstIterator();
        while (!it2.end())
        {
            auto id = (*it2)->getVertexId();
            auto found = std::find(begin(vertexesInComponent), end(vertexesInComponent), id) !=
                         end(vertexesInComponent);

            if (!found)
                graph->removeVertex(*it2);

            ++it2;
        }
    }
};

template <class Graph, class Vertex>
class ConnectivityVisitor
{
public:
    ConnectivityVisitor(ConnectivityVerifier<Graph, Vertex>* observer) : observer(observer)
    {
    }

    /**
     * Method: visitVertex
     * -------------------
     * Description: Action invoked by Traverser when a node is reached. The goal of
     * the visitVertex method is to notify the ConnectivityVerifier class about the vertex/
     * @returns true if iterator should keep traversing
     */
    bool visitVertex(Vertex* vertex)
    {
        observer->visited(vertex->getVertexId());
        return true;
    }

private:
    ConnectivityVerifier<Graph, Vertex>* observer;
};
}
