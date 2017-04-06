/**
 * 2do cuatrimestre 2014
 * @author  Luciana Reznik
 */
#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <list>


#include "ComplexNets/DirectedVertexAspect.h"
#include "ComplexNets/AdjacencyListVertex.h"
#include "ComplexNets/AdjacencyListGraph.h"
#include "ComplexNets/GraphExceptions.h"
#include "ComplexNets/typedefs.h"
#include "ComplexNets/IGraphFactory.h"
#include "ComplexNets/DirectedDegreeDistribution.h"
#include "ComplexNets/GraphGenerator.h"
#include "ComplexNets/DirectedGraphFactory.h"


namespace directedDegreeDistributionTest
{

using namespace graphpp;
using namespace std;
using ::testing::Test;

class DirectedDegreeDistributionTest : public Test
{

protected:

    DirectedDegreeDistributionTest() { }

    virtual ~DirectedDegreeDistributionTest() { }


    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {

    }
public:
    typedef DirectedVertexAspect<Vertex> DirectedVertex;
    
    typedef AdjacencyListGraph<DirectedVertex> IndexedGraph;
    typedef AdjacencyListGraph<DirectedVertex, list<DirectedVertex*> > ListGraph;
    typedef AdjacencyListGraph<DirectedVertex, vector<DirectedVertex*> > VectorGraph;



};


TEST_F(DirectedDegreeDistributionTest, DirectedDegreeDistributionIndexed)
{

   
    IndexedGraph ig(true,false);
    //Create vertex
    DirectedVertex* x = new DirectedVertex(1);

    //create neighbor vertices
    DirectedVertex* v1 = new DirectedVertex(2);
    DirectedVertex* v2 = new DirectedVertex(3);
    DirectedVertex* v3 = new DirectedVertex(4);

    ig.addVertex(x);
    ig.addVertex(v1);
    ig.addVertex(v2);
    ig.addVertex(v3);

    ig.addEdge(x, v1);
    ig.addEdge(x, v2);
    ig.addEdge(x, v3);
    ig.addEdge(v1, v2);

    
    DirectedDegreeDistribution<IndexedGraph, DirectedVertex> distribution(ig);
    auto itIn = distribution.inDegreeIterator();
    auto itOut = distribution.outDegreeIterator();


    //there it should be 1 vertex of In degree 0
    ASSERT_EQ(itIn->first, 0);
    ASSERT_EQ(itIn->second, 1);

    ++itIn;

     //there it should be 2 vertex of In degree 1
    ASSERT_EQ(itIn->first, 1);
    ASSERT_EQ(itIn->second, 2);

    ++itIn;

     //there it should be 2 vertex of In degree 2
    ASSERT_EQ(itIn->first, 2);
    ASSERT_EQ(itIn->second, 1);

    

   
    //there it should be 2 vertex of Out degree 0
    ASSERT_EQ(itOut->first, 0);
    ASSERT_EQ(itOut->second, 2);

    ++itOut;

     //there it should be 1 vertex of Out degree 1
    ASSERT_EQ(itOut->first, 1);
    ASSERT_EQ(itOut->second, 1);

    ++itOut;

     //there it should be 1 vertex of Out degree 3
    ASSERT_EQ(itOut->first, 3);
    ASSERT_EQ(itOut->second, 1);

}


TEST_F(DirectedDegreeDistributionTest, DirectedDegreeDistributionList)
{

   
    ListGraph ig(true,false);
    //Create vertex
    DirectedVertex* x = new DirectedVertex(1);

    //create neighbor vertices
    DirectedVertex* v1 = new DirectedVertex(2);
    DirectedVertex* v2 = new DirectedVertex(3);
    DirectedVertex* v3 = new DirectedVertex(4);

    ig.addVertex(x);
    ig.addVertex(v1);
    ig.addVertex(v2);
    ig.addVertex(v3);

    ig.addEdge(x, v1);
    ig.addEdge(x, v2);
    ig.addEdge(x, v3);
    ig.addEdge(v1, v2);

    
    DirectedDegreeDistribution<ListGraph, DirectedVertex> distribution(ig);
    auto itIn = distribution.inDegreeIterator();
    auto itOut = distribution.outDegreeIterator();


    //there it should be 1 vertex of In degree 0
    ASSERT_EQ(itIn->first, 0);
    ASSERT_EQ(itIn->second, 1);

    ++itIn;

     //there it should be 2 vertex of In degree 1
    ASSERT_EQ(itIn->first, 1);
    ASSERT_EQ(itIn->second, 2);

    ++itIn;

     //there it should be 2 vertex of In degree 2
    ASSERT_EQ(itIn->first, 2);
    ASSERT_EQ(itIn->second, 1);

    

   
    //there it should be 2 vertex of Out degree 0
    ASSERT_EQ(itOut->first, 0);
    ASSERT_EQ(itOut->second, 2);

    ++itOut;

     //there it should be 1 vertex of Out degree 1
    ASSERT_EQ(itOut->first, 1);
    ASSERT_EQ(itOut->second, 1);

    ++itOut;

     //there it should be 1 vertex of Out degree 3
    ASSERT_EQ(itOut->first, 3);
    ASSERT_EQ(itOut->second, 1);

}

TEST_F(DirectedDegreeDistributionTest, DirectedDegreeDistributionVector)
{
    VectorGraph ig(true,false);
    
    //Create vertex
    DirectedVertex* x = new DirectedVertex(1);

    //create neighbor vertices
    DirectedVertex* v1 = new DirectedVertex(2);
    DirectedVertex* v2 = new DirectedVertex(3);
    DirectedVertex* v3 = new DirectedVertex(4);

    ig.addVertex(x);
    ig.addVertex(v1);
    ig.addVertex(v2);
    ig.addVertex(v3);

    ig.addEdge(x, v1);
    ig.addEdge(x, v2);
    ig.addEdge(x, v3);
    ig.addEdge(v1, v2);

    
    DirectedDegreeDistribution<VectorGraph, DirectedVertex> distribution(ig);
    auto itIn = distribution.inDegreeIterator();
    auto itOut = distribution.outDegreeIterator();


    //there it should be 1 vertex of In degree 0
    ASSERT_EQ(itIn->first, 0);
    ASSERT_EQ(itIn->second, 1);

    ++itIn;

     //there it should be 2 vertex of In degree 1
    ASSERT_EQ(itIn->first, 1);
    ASSERT_EQ(itIn->second, 2);

    ++itIn;

     //there it should be 2 vertex of In degree 2
    ASSERT_EQ(itIn->first, 2);
    ASSERT_EQ(itIn->second, 1);

    

   
    //there it should be 2 vertex of Out degree 0
    ASSERT_EQ(itOut->first, 0);
    ASSERT_EQ(itOut->second, 2);

    ++itOut;

     //there it should be 1 vertex of Out degree 1
    ASSERT_EQ(itOut->first, 1);
    ASSERT_EQ(itOut->second, 1);

    ++itOut;

     //there it should be 1 vertex of Out degree 3
    ASSERT_EQ(itOut->first, 3);
    ASSERT_EQ(itOut->second, 1);

}

TEST_F(DirectedDegreeDistributionTest, DirectedDegreeDistributionRealWorldTest)
{
    VectorGraph * g = new VectorGraph(true, true);
    GraphReader<VectorGraph, DirectedVertex> graphReader;

    graphReader.read(*g, "TestTrees/DirectedTree.txt");

    DirectedDegreeDistribution<VectorGraph, DirectedVertex> distribution(*g);
    auto itIn = distribution.inDegreeIterator();
    auto itOut = distribution.outDegreeIterator();


    ASSERT_EQ(itOut->first,1);
    ASSERT_EQ(itOut->second,2);
    ++itOut;

    ASSERT_EQ(itIn->first,2);
    ASSERT_EQ(itIn->second,2);
    ++itIn;

    ASSERT_EQ(itOut->first,3);
    ASSERT_EQ(itOut->second,3);
    ++itOut;

    ASSERT_EQ(itIn->first,3);
    ASSERT_EQ(itIn->second,3);
    ++itIn;

    ASSERT_EQ(itOut->first,4);
    ASSERT_EQ(itOut->second,2);
    ++itOut;

    ASSERT_EQ(itIn->first,4);
    ASSERT_EQ(itIn->second,2);
    ++itIn;

    ASSERT_EQ(itOut->first,5);
    ASSERT_EQ(itOut->second,1);
    ++itOut;

    ASSERT_EQ(itIn->first,5);
    ASSERT_EQ(itIn->second,2);
    ++itIn;

    ASSERT_EQ(itOut->first,6);
    ASSERT_EQ(itOut->second,1);
    ++itOut;
}

}
