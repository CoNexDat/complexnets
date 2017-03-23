// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

#pragma once

#include <math.h>
#include <vector>
#include "TraverserBFS.h"
#include "mili/mili.h"

namespace graphpp
{
template <class Graph, class Vertex>
class ConexityVisitor;

template <class Graph, class Vertex>
class ConexityVerifier
{
public:
    std::vector<unsigned int> vertexesLeft;
    std::vector<unsigned int> vertexesInComponent;
    typedef typename Vertex::VerticesIterator NeighborsIterator;

    ConexityVerifier()
    {
    }

    void visited(unsigned int id)
    {
        vertexesInComponent.push_back(id);
        // Erase vertex from vertexesLeft
        for (unsigned int i = 0; i < vertexesLeft.size(); i++)
        {
            if (vertexesLeft[i] == id)
            {
                vertexesLeft.erase(vertexesLeft.begin() + i);
                return;
            }
        }
    }

    void getBiggestComponent(Graph* graph)
    {
        AdjacencyListGraph<AdjacencyListVertex>::VerticesConstIterator it =
            graph->verticesConstIterator();
        while (!it.end())
        {
            vertexesLeft.push_back((*it)->getVertexId());
            ++it;
        }

        ConexityVisitor<Graph, Vertex> visitor(this);
        do
        {
            vertexesInComponent.clear();
            Vertex* source = graph->getVertexById(vertexesLeft.back());
            vertexesLeft.pop_back();
            TraverserBFS<Graph, Vertex, ConexityVisitor<Graph, Vertex>>::traverse(source, visitor);
        } while (!vertexesLeft.empty() && vertexesInComponent.size() < graph->verticesCount() / 2);

        // if(vertexesInComponent.size() >= graph->verticesCount()/2)
        // cout << "Component found\n";

        AdjacencyListGraph<AdjacencyListVertex>::VerticesConstIterator it2 =
            graph->verticesConstIterator();
        while (!it2.end())
        {
            bool found = false;
            for (unsigned int i = 0; i < vertexesInComponent.size(); i++)
            {
                if (vertexesInComponent[i] == (*it2)->getVertexId())
                {
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                // cout << "Remove ";
                // cout << (*it2)->getVertexId();
                // cout << "\n";
                graph->removeVertex(*it2);
            }

            ++it2;
        }
    }
};

template <class Graph, class Vertex>
class ConexityVisitor
{
public:
    ConexityVisitor(ConexityVerifier<Graph, Vertex>* conexityVerifierObserver)
    {
        this->conexityVerifierObserver = conexityVerifierObserver;
    }

    /**
     * Method: visitVertex
     * -------------------
     * Description: Action invoked by Traverser when a node is reached. The goal of
     * the visitVertex method is to notify the ConexityVerifier class about the vertex/
     * @returns true if iterator should keep traversing
     */
    bool visitVertex(Vertex* vertex)
    {
        conexityVerifierObserver->visited(vertex->getVertexId());
        return true;
    }

private:
    ConexityVerifier<Graph, Vertex>* conexityVerifierObserver;
};
}
