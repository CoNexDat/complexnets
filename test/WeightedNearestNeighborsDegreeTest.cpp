
#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <list>

#include "ComplexNets/AdjacencyListVertex.h"
#include "ComplexNets/AdjacencyListGraph.h"
#include "ComplexNets/GraphExceptions.h"
#include "ComplexNets/WeightedGraphAspect.h"
#include "ComplexNets/WeightedVertexAspect.h"
#include "ComplexNets/WeightedNearestNeighborsDegree.h"

namespace weightedNearestNeighborsDegreeTest
{

using namespace graphpp;
using namespace std;
using ::testing::Test;

class WeightedNearestNeighborsDegreeTest : public Test
{

protected:

    WeightedNearestNeighborsDegreeTest() { }

    virtual ~WeightedNearestNeighborsDegreeTest() { }


    virtual void SetUp()
    {

    }

    virtual void TearDown()
    {

    }
public:
    typedef WeightedVertexAspect<AdjacencyListVertex> Vertex;
    typedef AdjacencyListGraph<Vertex> Graph;
    typedef WeightedGraphAspect<Vertex, Graph> WeightedGraph;


};


TEST_F(WeightedNearestNeighborsDegreeTest , GeneralGraph)
{
    WeightedGraph g;
    Vertex* x = new Vertex(1);
    Vertex* v1 = new Vertex(2);
    Vertex* v2 = new Vertex(3);
    Vertex* v3 = new Vertex(4);
    Vertex* v4 = new Vertex(5);
    Vertex* v5 = new Vertex(6);

    Vertex* v5_1 = new Vertex(7);
    Vertex* v5_2 = new Vertex(8);
    Vertex* v5_3 = new Vertex(9);
    Vertex* v5_4 = new Vertex(10);
    g.addVertex(x);
    g.addVertex(v1);
    g.addVertex(v2);
    g.addVertex(v3);
    g.addVertex(v4);
    g.addVertex(v5);

    g.addEdge(x, v1, 1);
    g.addEdge(x, v2, 1);
    g.addEdge(x, v3, 1);
    g.addEdge(x, v4, 1);
    g.addEdge(x, v5, 5);

    g.addEdge(v5, v5_1, 1.4);
    g.addEdge(v5, v5_2, 5.8);
    g.addEdge(v5, v5_3, 9.2);
    g.addEdge(v5, v5_4, 0.6);

    typedef WeightedNearestNeighborsDegree<WeightedGraph, Vertex> Knn;
    Knn knn;

    double dx = knn.meanDegreeForVertex(x);
    double epsilon = 0.001;
    ASSERT_TRUE(fabs(dx - 3.222) <  epsilon);

    double dv1 = knn.meanDegreeForVertex(v1);
    ASSERT_TRUE(fabs(dv1 - 5.0) <  epsilon);

    double dv5 = knn.meanDegreeForVertex(v5);
    ASSERT_TRUE(fabs(dv5 - 1.909) <  epsilon);

    double average = knn.meanDegree(g, Vertex::Degree(5));

    ASSERT_TRUE(fabs(average - 2.565) <  epsilon);
}

TEST_F(WeightedNearestNeighborsDegreeTest , SingleNodeGraph)
{
    typedef WeightedNearestNeighborsDegree<WeightedGraph, Vertex> Knn;
    Knn knn;
    WeightedGraph g;
    Vertex* x = new Vertex(1);
    g.addVertex(x);
    double dx = knn.meanDegreeForVertex(x);
    double epsilon = 0.001;
    ASSERT_TRUE(fabs(dx - 0.0) <  epsilon);
}
}

