
#include <gtest/gtest.h>

#include "../src/ComplexNets/AdjacencyListVertex.h"

namespace adjacencyListVertexTest
{

using namespace graphpp;
using ::testing::Test;

typedef AdjacencyListVertex Vertex;

class AdjacencyListVertexTest : public Test
{
protected:

    AdjacencyListVertexTest() { }

    virtual ~AdjacencyListVertexTest() { }


    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {

    }
};

TEST_F(AdjacencyListVertexTest, VertexIdTest)
{
    //Create vertex
    AdjacencyListVertex* v = new AdjacencyListVertex(1);

    ASSERT_EQ(v->getVertexId(), 1);

    delete v;
}

TEST_F(AdjacencyListVertexTest, AddIterationTest)
{
    //Create vertex
    AdjacencyListVertex* v = new AdjacencyListVertex(1);

    //create neighbor vertices
    AdjacencyListVertex* n1 = new AdjacencyListVertex(2);
    AdjacencyListVertex* n2 = new AdjacencyListVertex(3);
    AdjacencyListVertex* n3 = new AdjacencyListVertex(4);

    //add some neighbors
    v->addEdge(n1);
    v->addEdge(n2);
    v->addEdge(n3);

    //iterate through the neighbors, verifying they are the added
    Vertex::VerticesIterator it = v->neighborsIterator();
    int i = 2;
    while (!it.end())
    {
        Vertex* n  = *it;
        ASSERT_EQ(n->getVertexId(), i);
        i++;
        it++;
    }
    ASSERT_EQ(i, 5);

    delete v;
    delete n1;
    delete n2;
    delete n3;
}

TEST_F(AdjacencyListVertexTest, DegreeTest)
{
    //Create vertex
    AdjacencyListVertex* v = new AdjacencyListVertex(1);

    //check that degree is 0
    ASSERT_EQ(v->degree(), 0);

    //create neighbor vertices
    AdjacencyListVertex* n1 = new AdjacencyListVertex(2);
    AdjacencyListVertex* n2 = new AdjacencyListVertex(3);
    AdjacencyListVertex* n3 = new AdjacencyListVertex(4);

    //add some neighbors and check degrees
    v->addEdge(n1);
    ASSERT_EQ(v->degree(), 1);
    v->addEdge(n2);
    ASSERT_EQ(v->degree(), 2);
    v->addEdge(n3);
    ASSERT_EQ(v->degree(), 3);

    delete v;
    delete n1;
    delete n2;
    delete n3;
}

TEST_F(AdjacencyListVertexTest, OperatorLessTest)
{
    //Create vertex
    AdjacencyListVertex* v = new AdjacencyListVertex(1);
    AdjacencyListVertex* other = new AdjacencyListVertex(2);

    //check that v < other
    ASSERT_TRUE(v < other);

    delete v;
    delete other;
}

TEST_F(AdjacencyListVertexTest, IsNeighbourOfTest)
{
    //Create vertex
    AdjacencyListVertex* v = new AdjacencyListVertex(1);

    //create neighbor vertices
    AdjacencyListVertex* n1 = new AdjacencyListVertex(2);
    AdjacencyListVertex* n2 = new AdjacencyListVertex(3);

    //add some neighbors and check isNeighbourOf

    ASSERT_FALSE(v->isNeighbourOf(n1));
    v->addEdge(n1);
    ASSERT_TRUE(v->isNeighbourOf(n1));
    ASSERT_FALSE(v->isNeighbourOf(n2));
    v->addEdge(n2);
    ASSERT_TRUE(v->isNeighbourOf(n2));

    delete v;
    delete n1;
    delete n2;
}
}

