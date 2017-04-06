#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <list>

#include "ComplexNets/AdjacencyListVertex.h"
#include "ComplexNets/AdjacencyListGraph.h"
#include "ComplexNets/SimpleTextGraphReader.h"

namespace simpleTextGraphReaderTest
{

using namespace graphpp;
using namespace std;
using ::testing::Test;

class SimpleTextGraphReaderTest : public Test
{

protected:

    SimpleTextGraphReaderTest() { }

    virtual ~SimpleTextGraphReaderTest() { }


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


/*TEST_F(SimpleTextGraphReaderTest , FileDoesntExist)
{
    Graph g;
    SimpleTextGraphReader<Graph, Vertex> graphReader;

    ASSERT_THROW(graphReader.read(g, "TestTrees/tree0.txt"), FileNotFoundException);
}

TEST_F(SimpleTextGraphReaderTest , AllNodesLoaded)
{
    Graph g;
    SimpleTextGraphReader<Graph, Vertex> graphReader;

    graphReader.read(g, "TestTrees/tree1.txt");

    vector<bool> found(3, false);

    Graph::VerticesIterator it = g.verticesIterator();
    int i = 1;
    while (!it.end())
    {
        Vertex* n  = *it;
        found[n->getVertexId() - 1] = true;
        ++i;
        ++it;
    }
    for (unsigned int i = 0; i < 3; i++)
        ASSERT_TRUE(found[i]);
}

TEST_F(SimpleTextGraphReaderTest , EdgeCreation)
{
    Graph g2;
    SimpleTextGraphReader<Graph, Vertex> graphReader;

    ASSERT_NO_THROW(graphReader.read(g2, "TestTrees/tree1.txt"));

    Graph::VerticesIterator it = g2.verticesIterator();
    Vertex* n1  = *it;
    std::cout << "n1 id: " << n1->getVertexId() << std::endl;
    ++it;
    Vertex* n2  = *it;
    std::cout << "n2 id: " << n2->getVertexId() << std::endl;
    ++it;
    Vertex* n3  = *it;
    std::cout << "n3 id: " << n3->getVertexId() << std::endl;
    ASSERT_TRUE(n1->isNeighbourOf(n3));
    ASSERT_FALSE(n1->isNeighbourOf(n2));
    ASSERT_TRUE(n3->isNeighbourOf(n2));
}

TEST_F(SimpleTextGraphReaderTest , NegativeUnsignedInteger)
{
}

TEST_F(SimpleTextGraphReaderTest , VertexIdContainsAlphaCharacters)
{
}

TEST_F(SimpleTextGraphReaderTest , DiferentSpacingBetweenVertexId)
{
}

TEST_F(SimpleTextGraphReaderTest , EmptyLines)
{
}

TEST_F(SimpleTextGraphReaderTest , WeigthedGraph)
{
}

TEST_F(SimpleTextGraphReaderTest , CorrectWeigth)
{
}

TEST_F(SimpleTextGraphReaderTest , IntegerInsteadOfDouble)
{
}

TEST_F(SimpleTextGraphReaderTest , CorrectDecimalSeparator)
{
}

TEST_F(SimpleTextGraphReaderTest , WeigthedAndNotWeigthedGraph)
{
}

TEST_F(SimpleTextGraphReaderTest , MultipleComponents)
{
}*/

}

