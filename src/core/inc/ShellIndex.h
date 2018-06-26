#pragma once

#include "IShellIndex.h"
#include "typedefs.h"

namespace graphpp
{
typedef struct Node
{
    Vertex* vertex;
    int currentDegree;
} Node;

template <class Graph, class Vertex>
class ShellIndex : public IShellIndex<Graph, Vertex>
{
public:
    typedef typename IShellIndex<Graph, Vertex>::ShellIndexContainer ShellIndexContainer;
    typedef typename IShellIndex<Graph, Vertex>::ShellIndexIterator ShellIndexIterator;

    ShellIndex(Graph& g)
    {
        totalVertexes = initMap(g);
        initMultimapSet(g);
        calculateShellIndex();
    }

    virtual ShellIndexIterator iterator()
    {
        return ShellIndexIterator(shellIndex);
    }

private:
    Node* getNextNode()
    {
        for (int i = 0; i < totalVertexes; i++)
        {
            if (!nodesByCurrentDegree[i].empty())
            {
                return nodesByCurrentDegree[i].front();
            }
        }
        return nullptr;
    }

    void calculateShellIndex()
    {
        int k = 0;
        // While there are remaining vertices in the graph
        // Select the vertex with the lowest current degree
        while (getNextNode() != nullptr)
        {
            Node* nextVertex = getNextNode();
            Vertex* v = nextVertex->vertex;
            int degree = nextVertex->currentDegree;

            // If the degree is higher than k, then we have a new higher k-core
            // If lower, then it belongs to the actual k-core
            if (degree > k)
            {
                k = degree;
            }
            // Setting the coreness as the current k.
            shellIndex[v->getVertexId()] = k;
            // Will mark it as removed from the structure, since the coreness is already calculated
            nodesByVertexId[v->getVertexId()]->currentDegree = 0;
            nodesByCurrentDegree[degree].remove(nextVertex);

            NeighbourConstIterator neighborsIt = v->neighborsConstIterator();
            // Iterate through each of it's neighbors to reduce their degree by 1, since v was
            // removed.
            while (!neighborsIt.end())
            {
                Vertex* neigh = *neighborsIt;
                // Get the vertex node to be able to lower it one level in the structure
                Node* neighNode = nodesByVertexId[neigh->getVertexId()];

                if (neighNode->currentDegree > 0)
                {
                    // Remove it from the current level
                    nodesByCurrentDegree[neighNode->currentDegree].remove(neighNode);
                    neighNode->currentDegree--;

                    if (neighNode->currentDegree > 0)
                    {
                        // Re add it to a lower level if it still has a valid degree
                        nodesByCurrentDegree[neighNode->currentDegree].push_back(neighNode);
                    }
                    else
                    {
                        // Remove it and set coreness if the degree dropped to 0
                        shellIndex[neighNode->vertex->getVertexId()] = k;
                    }
                }
                ++neighborsIt;
            }
        }
    }

    int initMap(Graph& g)
    {
        VerticesConstIterator it = g.verticesConstIterator();
        int total = 0;

        // initialize all elements in zero
        while (!it.end())
        {
            Vertex* v = *it;
            shellIndex.insert(
                std::pair<typename Vertex::VertexId, unsigned int>(v->getVertexId(), 0));
            ++it;
            total++;
        }
        return total;
    }

    void initMultimapSet(Graph& g)
    {
        VerticesConstIterator it = g.verticesConstIterator();
        nodesByVertexId = new Node*[totalVertexes + 1];  // will not use index 0
        nodesByCurrentDegree =
            new std::list<Node*>[totalVertexes];  // 0 won't exist, still max degree possible is n-1

        // initialize all elements using the vertex id and the vertex degree
        while (!it.end())
        {
            Vertex* v = *it;
            Node* newNode = new Node();
            newNode->currentDegree = v->degree();
            newNode->vertex = v;
            nodesByVertexId[v->getVertexId()] = newNode;
            nodesByCurrentDegree[v->degree()].push_back(newNode);
            ++it;
        }
    }

    typedef typename Graph::VerticesConstIterator VerticesConstIterator;
    typedef typename Vertex::VerticesConstIterator NeighbourConstIterator;

    // This container will be set with the coreness of each vertex when found.
    ShellIndexContainer shellIndex;

    // This structure represents an array of node pointers.
    // This nodes are the different node-vertexes in the main structure
    // The index of the array represents the id of the node.
    // Used to get the node structure in O(1), to allow it to be moved to another list.
    Node** nodesByVertexId;
    // This is the main structure, contains an array of linked lists.
    // The index of the array represents the current degree of the vertexes stored on that list.
    // The lists are doubly-linked lists to allow a node representation to be easily removed.
    std::list<Node*>* nodesByCurrentDegree;
    int totalVertexes;
};
}  // namespace graphpp
