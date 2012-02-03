
#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <list>

#include "../complexnets/AdjacencyListVertex.h"
#include "../complexnets/AdjacencyListGraph.h"
#include "../complexnets/GraphExceptions.h"

namespace adjacencyListGraphTest
{

using namespace graphpp;
using namespace std;
using ::testing::Test;

typedef AdjacencyListVertex Vertex;
typedef AdjacencyListGraph<Vertex> IndexedGraph;
typedef AdjacencyListGraph<Vertex, list<Vertex*> > ListGraph;
typedef AdjacencyListGraph<Vertex, vector<Vertex*> > VectorGraph;

class AdjacencyListGraphTest : public Test
{
protected:

    AdjacencyListGraphTest() { }

    virtual ~AdjacencyListGraphTest() { }


    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {

    }
};

TEST_F(AdjacencyListGraphTest, IndexedAddVertexIterationTest)
{
    IndexedGraph g;
    //Create vertex
    Vertex* v = new Vertex(1);

    //create neighbor vertices
    Vertex* n1 = new Vertex(2);
    Vertex* n2 = new Vertex(3);
    Vertex* n3 = new Vertex(4);

    g.addVertex(v);
    g.addVertex(n1);
    g.addVertex(n2);
    g.addVertex(n3);

    //vector holding found ids, since set iteration order isnt forward
    vector<bool> found(4, false);

    //iterate through the neighbors, verifying they are the added
    IndexedGraph::VerticesIterator it = g.verticesIterator();
    int i = 1;
    while (!it.end())
    {
        Vertex* n  = *it;

        found[n->getVertexId() - 1] = true;
        i++;
        ++it;
    }

    //iterate found and verify all 4 elements were found
    for (unsigned int i = 0; i < 4; i++)
        ASSERT_TRUE(found[i]);
}

TEST_F(AdjacencyListGraphTest, IndexedAddEdgeTest)
{
    IndexedGraph g;
    //Create vertex
    Vertex* v = new Vertex(1);

    //create neighbor vertices
    Vertex* n1 = new Vertex(2);
    Vertex* n2 = new Vertex(3);
    Vertex* n3 = new Vertex(4);

    g.addVertex(v);
    g.addVertex(n1);
    g.addVertex(n2);
    g.addVertex(n3);

    g.addEdge(v, n1);

    ASSERT_TRUE(v->isNeighbourOf(n1));
    ASSERT_TRUE(n1->isNeighbourOf(v));
    ASSERT_FALSE(v->isNeighbourOf(n2));
    ASSERT_FALSE(v->isNeighbourOf(n3));

    g.addEdge(v, n3);

    ASSERT_TRUE(v->isNeighbourOf(n3));
}

TEST_F(AdjacencyListGraphTest, VerticesCountTest)
{
    IndexedGraph g;
    //Create vertex
    Vertex* v = new Vertex(1);

    //create neighbor vertices
    Vertex* n1 = new Vertex(2);
    Vertex* n2 = new Vertex(3);
    Vertex* n3 = new Vertex(4);

    ASSERT_EQ(g.verticesCount(), 0);

    g.addVertex(v);
    g.addVertex(n1);
    g.addVertex(n2);
    g.addVertex(n3);


    ASSERT_EQ(g.verticesCount(), 4);
}

TEST_F(AdjacencyListGraphTest, IndexedDuplicateEdgeTest)
{
    IndexedGraph g;
    //Create vertex
    Vertex* v = new Vertex(1);

    //create neighbor vertices
    Vertex* n1 = new Vertex(2);

    g.addVertex(v);
    g.addVertex(n1);

    g.addEdge(v, n1);

    ASSERT_TRUE(v->isNeighbourOf(n1));

    //the expected behaviour when adding duplicate edge to base graph class
    //is to get DuplicateEdge generic Exception
    ASSERT_THROW(g.addEdge(v, n1), DuplicateEdge);
}

TEST_F(AdjacencyListGraphTest, ListAddVertexIterationTest)
{
    ListGraph g;
    //Create vertex
    Vertex* v = new Vertex(1);

    //create neighbor vertices
    Vertex* n1 = new Vertex(2);
    Vertex* n2 = new Vertex(3);
    Vertex* n3 = new Vertex(4);

    g.addVertex(v);
    g.addVertex(n1);
    g.addVertex(n2);
    g.addVertex(n3);


    //iterate through the neighbors, verifying they are the added
    ListGraph::VerticesIterator it = g.verticesIterator();
    int i = 1;
    while (!it.end())
    {
        Vertex* n  = *it;

        ASSERT_EQ(n->getVertexId(), i);
        i++;
        ++it;
    }
}

TEST_F(AdjacencyListGraphTest, ListAddEdgeTest)
{
    ListGraph g;
    //Create vertex
    Vertex* v = new Vertex(1);

    //create neighbor vertices
    Vertex* n1 = new Vertex(2);
    Vertex* n2 = new Vertex(3);
    Vertex* n3 = new Vertex(4);

    g.addVertex(v);
    g.addVertex(n1);
    g.addVertex(n2);
    g.addVertex(n3);

    g.addEdge(v, n1);

    ASSERT_TRUE(v->isNeighbourOf(n1));
    ASSERT_TRUE(n1->isNeighbourOf(v));
    ASSERT_FALSE(v->isNeighbourOf(n2));
    ASSERT_FALSE(v->isNeighbourOf(n3));

    g.addEdge(v, n3);

    ASSERT_TRUE(v->isNeighbourOf(n3));
}

TEST_F(AdjacencyListGraphTest, ListDuplicateEdgeTest)
{
    ListGraph g;
    //Create vertex
    Vertex* v = new Vertex(1);

    //create neighbor vertices
    Vertex* n1 = new Vertex(2);

    g.addVertex(v);
    g.addVertex(n1);

    g.addEdge(v, n1);

    ASSERT_TRUE(v->isNeighbourOf(n1));

    //the expected behaviour when adding duplicate edge to base graph class
    //is to get DuplicateEdge generic Exception
    ASSERT_THROW(g.addEdge(v, n1), DuplicateEdge);
}

TEST_F(AdjacencyListGraphTest, VectorAddVertexIterationTest)
{
    VectorGraph g;
    //Create vertex
    Vertex* v = new Vertex(1);

    //create neighbor vertices
    Vertex* n1 = new Vertex(2);
    Vertex* n2 = new Vertex(3);
    Vertex* n3 = new Vertex(4);

    g.addVertex(v);
    g.addVertex(n1);
    g.addVertex(n2);
    g.addVertex(n3);


    //iterate through the neighbors, verifying they are the added
    VectorGraph::VerticesIterator it = g.verticesIterator();
    int i = 1;
    while (!it.end())
    {
        Vertex* n  = *it;

        ASSERT_EQ(n->getVertexId(), i);
        i++;
        ++it;
    }
}

TEST_F(AdjacencyListGraphTest, VectorAddEdgeTest)
{
    VectorGraph g;
    //Create vertex
    Vertex* v = new Vertex(1);

    //create neighbor vertices
    Vertex* n1 = new Vertex(2);
    Vertex* n2 = new Vertex(3);
    Vertex* n3 = new Vertex(4);

    g.addVertex(v);
    g.addVertex(n1);
    g.addVertex(n2);
    g.addVertex(n3);

    g.addEdge(v, n1);

    ASSERT_TRUE(v->isNeighbourOf(n1));
    ASSERT_TRUE(n1->isNeighbourOf(v));
    ASSERT_FALSE(v->isNeighbourOf(n2));
    ASSERT_FALSE(v->isNeighbourOf(n3));

    g.addEdge(v, n3);

    ASSERT_TRUE(v->isNeighbourOf(n3));
}

TEST_F(AdjacencyListGraphTest, VectorDuplicateEdgeTest)
{
    VectorGraph g;
    //Create vertex
    Vertex* v = new Vertex(1);

    //create neighbor vertices
    Vertex* n1 = new Vertex(2);

    g.addVertex(v);
    g.addVertex(n1);

    g.addEdge(v, n1);

    ASSERT_TRUE(v->isNeighbourOf(n1));

    //the expected behaviour when adding duplicate edge to base graph class
    //is to get DuplicateEdge generic Exception
    ASSERT_THROW(g.addEdge(v, n1), DuplicateEdge);
}

}

