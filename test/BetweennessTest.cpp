
#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <list>

#include "ComplexNets/AdjacencyListVertex.h"
#include "ComplexNets/AdjacencyListGraph.h"
#include "ComplexNets/GraphExceptions.h"
#include "ComplexNets/Betweenness.h"

namespace betweennessTest
{

using namespace graphpp;
using namespace std;
using ::testing::Test;

class BetweennessTest : public Test
{

protected:

    BetweennessTest() { }

    virtual ~BetweennessTest() { }


    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {

    }
public:
    typedef AdjacencyListVertex Vertex;
    typedef AdjacencyListGraph<Vertex> IndexedGraph;
    typedef AdjacencyListGraph<Vertex, list<Vertex*> > ListGraph;
    typedef AdjacencyListGraph<Vertex, vector<Vertex*> > VectorGraph;

};


TEST_F(BetweennessTest , BetweennessTest)
{
    IndexedGraph ig;
    //Create vertex
    Vertex* x = new Vertex(1);

    //create neighbor vertices
    Vertex* v1 = new Vertex(2);
    Vertex* v2 = new Vertex(3);
    Vertex* v3 = new Vertex(4);
    Vertex* v4 = new Vertex(5);

    ig.addVertex(x);
    ig.addVertex(v1);
    ig.addVertex(v2);
    ig.addVertex(v3);
    ig.addVertex(v4);

    ig.addEdge(x, v1);
    ig.addEdge(x, v2);
    ig.addEdge(x, v3);
    ig.addEdge(v1, v2);
    ig.addEdge(x, v4);

    Betweenness<IndexedGraph, Vertex> betweenness {ig};

    auto it = betweenness.iterator();

    while (!it.end())
    {
        std::cout << "----------" << std::endl;
        std::cout << "Id" << std::endl;
        std::cout << it->first << std::endl;
        std::cout << "Betweenness" << std::endl;
        std::cout << it->second << std::endl;
        ++it;
    }
}

}

