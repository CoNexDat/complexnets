
#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <list>

#include "../src/ComplexNets/AdjacencyListVertex.h"
#include "../src/ComplexNets/AdjacencyListGraph.h"
#include "../src/ComplexNets/GraphExceptions.h"
#include "../src/ComplexNets/ShellIndex.h"

namespace betweennessTest
{

using namespace graphpp;
using namespace std;
using ::testing::Test;

class ShellIndexTest : public Test
{

protected:

    ShellIndexTest() { }

    virtual ~ShellIndexTest() { }


    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {

    }
public:
    typedef AdjacencyListVertex Vertex;
    typedef AdjacencyListGraph<Vertex> Graph;

};


TEST_F(ShellIndexTest , ShellIndexTest)
{
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
        if (it->first == 0)
            ASSERT_EQ(it->second, 0);
        else if (it->first == 1)
            ASSERT_EQ(it->second, 2);
        else if (it->first == 2)
            ASSERT_EQ(it->second, 2);
        else if (it->first == 3)
            ASSERT_EQ(it->second, 2);
        else if (it->first == 4)
            ASSERT_EQ(it->second, 2);
        else if (it->first == 5)
            ASSERT_EQ(it->second, 1);
        ++it;
    }
}

}

