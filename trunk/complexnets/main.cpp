// Console.cpp : main project file.

#include <list>
#include <set>
#include <vector>
#include <map>
#include <typeinfo>
#include <iostream>
#include "AdjacencyListGraph.h"
#include "AdjacencyListVertex.h"
#include "AdjacencyListEdge.h"
#include "Traverser.h"


using namespace graphpp;

struct EdgeInfo
{
    int weight;
};
struct DummyEdgeInfo
{
  
};

typedef AdjacencyListVertex<EdgeInfo> Vertex;
typedef AdjacencyListGraph<Vertex, EdgeInfo, std::set<Vertex> > Graph;

int main()
{    
    
    Vertex v(1);
    Vertex v2(2);
    Vertex v3(3);
    
    
    EdgeInfo i1;
    EdgeInfo i2;
    i1.weight = 2;
    i2.weight = 3;
    Graph g;
    
    g.addVertex(v);
    g.addVertex(v2);
    g.addVertex(v3);
    
    g.addEdge(v, v2, i1);
    g.addEdge(v, v3, i2);
    
    Graph::VerticesConstIterator iter = g.verticesConstIterator();
    
    while(!iter.end())
    {
        std::cout << iter->getVertexId() << std::endl;
        iter++;
    }

    Vertex::EdgesIterator it = v.edgesIterator();
    
    while(!it.end())
    {
        std::cout << "Id" << std::endl;
        std::cout << it->destination().getVertexId() << std::endl;
        it++;
    }
    
    std::cout << "bfs" << std::endl;
    
    COutVisitor<Vertex> visitor;
    Traverser<Graph, Vertex, COutVisitor<Vertex> >::TraverseBFS(v, visitor);
    
    return 0;
}


