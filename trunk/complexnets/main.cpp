// Console.cpp : main project file.

#include <list>
#include <set>
#include <vector>
#include <map>
#include <typeinfo>
#include <iostream>
#include "AdjacencyListGraph.h"
#include "AdjacencyListVertex.h"
#include "SimpleTextGraphReader.h"
#include "ShellIndex.h"


using namespace graphpp;

struct EdgeInfo
{
    int weight;
};
struct DummyEdgeInfo
{

};

typedef AdjacencyListVertex Vertex;
typedef AdjacencyListGraph<Vertex> Graph;

int main()
{
    /*Graph g;
    SimpleTextGraphReader<Graph, Vertex> graphReader;

    graphReader.read(g, "data.txt");

    std::cout << "Cantidad de nodos " << g.verticesCount() << std::endl;
    Graph::VerticesConstIterator iter = g.verticesConstIterator();

    while (!iter.end())
    {
        std::cout << (*iter)->getVertexId() << std::endl;
        iter++;
    }*/

    Graph g2;
    Vertex* v0 = new Vertex(0);
    Vertex* v1 = new Vertex(1);
    Vertex* v2 = new Vertex(2);
    Vertex* v3 = new Vertex(3);
    Vertex* v4 = new Vertex(4);
    Vertex* v5 = new Vertex(5);
    g2.addVertex(v0);
    g2.addVertex(v1);
    g2.addVertex(v2);
    g2.addVertex(v3);
    g2.addVertex(v4);
    g2.addVertex(v5);
    g2.addEdge(v1, v2);
    g2.addEdge(v2, v3);
    g2.addEdge(v3, v4);
    g2.addEdge(v4, v1);
    g2.addEdge(v3, v5);
    ShellIndex<Graph, Vertex> shellIndex(g2);

    ShellIndex<Graph, Vertex>::ShellIndexIterator it = shellIndex.iterator();
    while (!it.end())
    {
        std::cout << "VertexId: " << it->first << " Core: " << it->second << std::endl;
        ++it;
    }

    return 0;
}


