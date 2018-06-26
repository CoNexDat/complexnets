
#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <list>

#include "AdjacencyListVertex.h"
#include "AdjacencyListGraph.h"
#include "GraphExceptions.h"
#include "typedefs.h"
#include "DegreeDistribution.h"
#include "GraphReader.h"

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

    auto it = distribution.iterator();

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

    auto it = distribution.iterator();

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

    auto it = distribution.iterator();

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


TEST_F(DegreeDistributionTest, DegreeDistributionRealWorldTest)
{
    VectorGraph * g = new VectorGraph(false, true);
    GraphReader<VectorGraph, Vertex> graphReader;

    graphReader.read(*g, "TestTrees/AS_CAIDA_2008.txt");

    DegreeDistribution<VectorGraph, Vertex> distribution(*g);

    auto it = distribution.iterator();

    // Check for the same structure as the AS_CAIDA_2008 file

    ASSERT_EQ(it->first,1);
    ASSERT_EQ(it->second,2511);
    ++it;
    ASSERT_EQ(it->first,2);
    ASSERT_EQ(it->second,2319);
    ++it;
    ASSERT_EQ(it->first,3);
    ASSERT_EQ(it->second,1073);
    ++it;
    ASSERT_EQ(it->first,4);
    ASSERT_EQ(it->second,541);
    ++it;
    ASSERT_EQ(it->first,5);
    ASSERT_EQ(it->second,341);
    ++it;
    ASSERT_EQ(it->first,6);
    ASSERT_EQ(it->second,214);
    ++it;
    ASSERT_EQ(it->first,7);
    ASSERT_EQ(it->second,163);
    ++it;
    ASSERT_EQ(it->first,8);
    ASSERT_EQ(it->second,113);
    ++it;
    ASSERT_EQ(it->first,9);
    ASSERT_EQ(it->second,67);
    ++it;
    ASSERT_EQ(it->first,10);
    ASSERT_EQ(it->second,60);
    ++it;
    ASSERT_EQ(it->first,11);
    ASSERT_EQ(it->second,47);
    ++it;
    ASSERT_EQ(it->first,12);
    ASSERT_EQ(it->second,34);
    ++it;
    ASSERT_EQ(it->first,13);
    ASSERT_EQ(it->second,41);
    ++it;
    ASSERT_EQ(it->first,14);
    ASSERT_EQ(it->second,27);
    ++it;
    ASSERT_EQ(it->first,15);
    ASSERT_EQ(it->second,26);
    ++it;
    ASSERT_EQ(it->first,16);
    ASSERT_EQ(it->second,22);
    ++it;
    ASSERT_EQ(it->first,17);
    ASSERT_EQ(it->second,17);
    ++it;
    ASSERT_EQ(it->first,18);
    ASSERT_EQ(it->second,23);
    ++it;
    ASSERT_EQ(it->first,19);
    ASSERT_EQ(it->second,16);
    ++it;
    ASSERT_EQ(it->first,20);
    ASSERT_EQ(it->second,12);
    ++it;
    ASSERT_EQ(it->first,21);
    ASSERT_EQ(it->second,18);
    ++it;
    ASSERT_EQ(it->first,22);
    ASSERT_EQ(it->second,15);
    ++it;
    ASSERT_EQ(it->first,23);
    ASSERT_EQ(it->second,7);
    ++it;
    ASSERT_EQ(it->first,24);
    ASSERT_EQ(it->second,9);
    ++it;
    ASSERT_EQ(it->first,25);
    ASSERT_EQ(it->second,18);
    ++it;
    ASSERT_EQ(it->first,26);
    ASSERT_EQ(it->second,10);
    ++it;
    ASSERT_EQ(it->first,27);
    ASSERT_EQ(it->second,5);
    ++it;
    ASSERT_EQ(it->first,28);
    ASSERT_EQ(it->second,5);
    ++it;
    ASSERT_EQ(it->first,29);
    ASSERT_EQ(it->second,3);
    ++it;
    ASSERT_EQ(it->first,30);
    ASSERT_EQ(it->second,3);
    ++it;
    ASSERT_EQ(it->first,31);
    ASSERT_EQ(it->second,5);
    ++it;
    ASSERT_EQ(it->first,32);
    ASSERT_EQ(it->second,5);
    ++it;
    ASSERT_EQ(it->first,33);
    ASSERT_EQ(it->second,5);
    ++it;
    ASSERT_EQ(it->first,34);
    ASSERT_EQ(it->second,5);
    ++it;
    ASSERT_EQ(it->first,35);
    ASSERT_EQ(it->second,4);
    ++it;
    ASSERT_EQ(it->first,36);
    ASSERT_EQ(it->second,5);
    ++it;
    ASSERT_EQ(it->first,37);
    ASSERT_EQ(it->second,2);
    ++it;
    ASSERT_EQ(it->first,38);
    ASSERT_EQ(it->second,6);
    ++it;
    ASSERT_EQ(it->first,39);
    ASSERT_EQ(it->second,4);
    ++it;
    ASSERT_EQ(it->first,40);
    ASSERT_EQ(it->second,2);
    ++it;
    ASSERT_EQ(it->first,41);
    ASSERT_EQ(it->second,3);
    ++it;
    ASSERT_EQ(it->first,42);
    ASSERT_EQ(it->second,2);
    ++it;
    ASSERT_EQ(it->first,43);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,44);
    ASSERT_EQ(it->second,2);
    ++it;
    ASSERT_EQ(it->first,45);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,46);
    ASSERT_EQ(it->second,4);
    ++it;
    ASSERT_EQ(it->first,47);
    ASSERT_EQ(it->second,3);
    ++it;
    ASSERT_EQ(it->first,48);
    ASSERT_EQ(it->second,4);
    ++it;
    ASSERT_EQ(it->first,49);
    ASSERT_EQ(it->second,2);
    ++it;
    ASSERT_EQ(it->first,50);
    ASSERT_EQ(it->second,2);
    ++it;
    ASSERT_EQ(it->first,51);
    ASSERT_EQ(it->second,2);
    ++it;
    ASSERT_EQ(it->first,52);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,53);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,55);
    ASSERT_EQ(it->second,2);
    ++it;
    ASSERT_EQ(it->first,56);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,57);
    ASSERT_EQ(it->second,2);
    ++it;
    ASSERT_EQ(it->first,59);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,61);
    ASSERT_EQ(it->second,2);
    ++it;
    ASSERT_EQ(it->first,62);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,66);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,67);
    ASSERT_EQ(it->second,2);
    ++it;
    ASSERT_EQ(it->first,68);
    ASSERT_EQ(it->second,2);
    ++it;
    ASSERT_EQ(it->first,71);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,73);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,74);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,76);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,82);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,86);
    ASSERT_EQ(it->second,2);
    ++it;
    ASSERT_EQ(it->first,87);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,88);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,89);
    ASSERT_EQ(it->second,3);
    ++it;
    ASSERT_EQ(it->first,99);
    ASSERT_EQ(it->second,2);
    ++it;
    ASSERT_EQ(it->first,101);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,108);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,110);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,115);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,116);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,119);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,123);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,133);
    ASSERT_EQ(it->second,2);
    ++it;
    ASSERT_EQ(it->first,135);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,140);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,150);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,167);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,172);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,193);
    ASSERT_EQ(it->second,2);
    ++it;
    ASSERT_EQ(it->first,210);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,215);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,217);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,221);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,234);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,244);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,271);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,272);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,286);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,289);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,303);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,324);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,405);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,487);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,547);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,559);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,614);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,646);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,678);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,692);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,838);
    ASSERT_EQ(it->second,1);
    ++it;
    ASSERT_EQ(it->first,1241);
    ASSERT_EQ(it->second,1);
    ++it;
}
}

