
#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <list>

#include "ComplexNets/AdjacencyListVertex.h"
#include "ComplexNets/AdjacencyListGraph.h"
#include "ComplexNets/GraphExceptions.h"
#include "ComplexNets/ClusteringCoefficient.h"
#include "ComplexNets/GraphReader.h"

namespace clusterCoefficientTest
{

using namespace graphpp;
using namespace std;
using ::testing::Test;

class ClusteringCoefficientTest : public Test
{

protected:

    ClusteringCoefficientTest() { }

    virtual ~ClusteringCoefficientTest() { }


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


TEST_F(ClusteringCoefficientTest , VertexGeneralTest)
{
    ListGraph ig;
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

    ClusteringCoefficient<ListGraph, Vertex> clustering;
    typedef Clustering::Coefficient Coef;

    Coef c = clustering.vertexClusteringCoefficient(x);

    Coef epsilon = 0.001;

    ASSERT_TRUE(fabs(c - 0.16667) <  epsilon);

    Coef c2 = clustering.clusteringCoefficient(ig, Vertex::Degree(4));
    ASSERT_TRUE(fabs(c2 - 0.16667) <  epsilon);
}

TEST_F(ClusteringCoefficientTest, FullGraphTest)
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
    ig.addEdge(v1, v3);
    ig.addEdge(v3, v2);

    ClusteringCoefficient<ListGraph, Vertex> clustering;
    typedef Clustering::Coefficient Coef;

    Coef c = clustering.vertexClusteringCoefficient(x);

    Coef epsilon = 0.001;

    ASSERT_TRUE(fabs(c - 1.0) <  epsilon);

    Coef c2 = clustering.clusteringCoefficient(ig, Vertex::Degree(3));
    ASSERT_TRUE(fabs(c2 - 1.0) <  epsilon);
}

TEST_F(ClusteringCoefficientTest, AcyclicGraphTest)
{
    ListGraph ig;
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
    ig.addEdge(v4, x);;

    ClusteringCoefficient<ListGraph, Vertex> clustering;
    typedef Clustering::Coefficient Coef;

    Coef c = clustering.vertexClusteringCoefficient(x);

    Coef epsilon = 0.001;

    ASSERT_TRUE(fabs(c - 0.0) <  epsilon);

    Coef c2 = clustering.clusteringCoefficient(ig, Vertex::Degree(4));
    ASSERT_TRUE(fabs(c2 - 0.0) <  epsilon);
}

TEST_F(ClusteringCoefficientTest, RealWorldTest)
{
    VectorGraph * g = new VectorGraph(false, false);
    GraphReader<VectorGraph, Vertex> graphReader;

    graphReader.read(*g, "TestTrees/AS_CAIDA_2008.txt");

    ClusteringCoefficient<ListGraph, Vertex> clustering;
    typedef Clustering::Coefficient Coef;

    Coef epsilon = 0.001;

    Vertex * x = g->getVertexById(3);
    Coef c = clustering.vertexClusteringCoefficient(x);
    ASSERT_TRUE(fabs(c - 0.6666667) <  epsilon);

    x = g->getVertexById(174);
    c = clustering.vertexClusteringCoefficient(x);
    ASSERT_TRUE(fabs(c - 0.01141431) <  epsilon);

    x = g->getVertexById(4);
    c = clustering.vertexClusteringCoefficient(x);

    /* This is 1.0 in Network Workbench, but because of how ComplexNets works
     * it throws error when supporting multiedges, so we either accept
     * this value, or we dont throw exception when reading multiedges*/
    ASSERT_TRUE(fabs(c - 1.0) <  epsilon);

    x = g->getVertexById(23148);
    c = clustering.vertexClusteringCoefficient(x);
    
    ASSERT_TRUE(fabs(c - 0.3583333) <  epsilon);
}
}

