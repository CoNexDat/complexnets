
#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <list>

#include "../complexnets/AdjacencyListVertex.h"
#include "../complexnets/AdjacencyListGraph.h"
#include "../complexnets/GraphExceptions.h"
#include "../complexnets/DegreeDistribution.h"

namespace degreeDistributionTest
{

using namespace graphpp;
using namespace std;
using ::testing::Test;

class DegreeDistributionTest : public Test
{

protected:

    DegreeDistributionTest() { }

    virtual ~DegreeDistributionTest() { }


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


TEST_F(DegreeDistributionTest, DegreeDistributionIndexed)
{
    IndexedGraph ig;
    //Create vertex
    Vertex* x = new Vertex(1);

    //create neighbor vertices
    Vertex* v1 = new Vertex(2);
    Vertex* v2 = new Vertex(3);
    Vertex* v3 = new Vertex(4);

    ig.addVertex(x);
    ig.addVertex(v1);
    ig.addVertex(v2);
    ig.addVertex(v3);

    ig.addEdge(x, v1);
    ig.addEdge(x, v2);
    ig.addEdge(x, v3);
    ig.addEdge(v1, v2);

    DegreeDistribution<IndexedGraph, Vertex> distribution(ig);

    DegreeDistribution<IndexedGraph, Vertex>::DistributionIterator it = distribution.distributionIterator();

    //there it should be 1 vertex of degree 1
    ASSERT_EQ(it->first, 1);
    ASSERT_EQ(it->second, 1);

    ++it;

    //there it should be 2 vertices of degree 2
    ASSERT_EQ(it->first, 2);
    ASSERT_EQ(it->second, 2);

    ++it;

    //there it should be 1 vertex of degree 3
    ASSERT_EQ(it->first, 3);
    ASSERT_EQ(it->second, 1);
}

TEST_F(DegreeDistributionTest, DegreeDistributionList)
{
    ListGraph ig;
    //Create vertex
    Vertex* x = new Vertex(1);

    //create neighbor vertices
    Vertex* v1 = new Vertex(2);
    Vertex* v2 = new Vertex(3);
    Vertex* v3 = new Vertex(4);

    ig.addVertex(x);
    ig.addVertex(v1);
    ig.addVertex(v2);
    ig.addVertex(v3);

    ig.addEdge(x, v1);
    ig.addEdge(x, v2);
    ig.addEdge(x, v3);
    ig.addEdge(v1, v2);

    DegreeDistribution<ListGraph, Vertex> distribution(ig);

    DegreeDistribution<ListGraph, Vertex>::DistributionIterator it = distribution.distributionIterator();

    //there it should be 1 vertex of degree 1
    ASSERT_EQ(it->first, 1);
    ASSERT_EQ(it->second, 1);

    ++it;

    //there it should be 2 vertices of degree 2
    ASSERT_EQ(it->first, 2);
    ASSERT_EQ(it->second, 2);

    ++it;

    //there it should be 1 vertex of degree 3
    ASSERT_EQ(it->first, 3);
    ASSERT_EQ(it->second, 1);
}

TEST_F(DegreeDistributionTest, DegreeDistributionVector)
{
    VectorGraph ig;
    //Create vertex
    Vertex* x = new Vertex(1);

    //create neighbor vertices
    Vertex* v1 = new Vertex(2);
    Vertex* v2 = new Vertex(3);
    Vertex* v3 = new Vertex(4);

    ig.addVertex(x);
    ig.addVertex(v1);
    ig.addVertex(v2);
    ig.addVertex(v3);

    ig.addEdge(x, v1);
    ig.addEdge(x, v2);
    ig.addEdge(x, v3);
    ig.addEdge(v1, v2);

    DegreeDistribution<VectorGraph, Vertex> distribution(ig);

    DegreeDistribution<VectorGraph, Vertex>::DistributionIterator it = distribution.distributionIterator();

    //there it should be 1 vertex of degree 1
    ASSERT_EQ(it->first, 1);
    ASSERT_EQ(it->second, 1);

    ++it;

    //there it should be 2 vertices of degree 2
    ASSERT_EQ(it->first, 2);
    ASSERT_EQ(it->second, 2);

    ++it;

    //there it should be 1 vertex of degree 3
    ASSERT_EQ(it->first, 3);
    ASSERT_EQ(it->second, 1);
}
}

