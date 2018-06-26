#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <list>

#include "AdjacencyListVertex.h"
#include "AdjacencyListGraph.h"
#include "GraphExceptions.h"
#include "WeightedGraphAspect.h"
#include "WeightedVertexAspect.h"
#include "WeightedClusteringCoefficient.h"

namespace weightedClusterCoefficientTest
{

using namespace graphpp;
using namespace std;
using ::testing::Test;

class WeightedClusterCoefficientTest : public Test
{

protected:

    WeightedClusterCoefficientTest() { }

    virtual ~WeightedClusterCoefficientTest() { }


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


TEST_F(WeightedClusterCoefficientTest, GeneralTest)
{
    WeightedGraph g;

    Vertex* x = new Vertex(1);
    Vertex* v1 = new Vertex(2);
    Vertex* v2 = new Vertex(3);
    Vertex* v3 = new Vertex(4);
    Vertex* v4 = new Vertex(5);

    g.addVertex(x);
    g.addVertex(v1);
    g.addVertex(v2);
    g.addVertex(v3);
    g.addVertex(v4);

    g.addEdge(x, v1, 1);
    g.addEdge(v1, v2, 1);
    g.addEdge(v2, v3, 1);
    g.addEdge(v3, x, 1);
    g.addEdge(x, v4, 5);
    g.addEdge(v3, v1, 1);
    g.addEdge(x, v2, 1);

    WeightedClusteringCoefficient<WeightedGraph, Vertex> clustering;

    double c = clustering.vertexClusteringCoefficient(x);

    double epsilon = 0.001;

    ASSERT_TRUE(fabs(c - 0.25) <  epsilon);

    double c2 = clustering.clusteringCoefficient(g, Vertex::Degree(4));
    ASSERT_TRUE(fabs(c2 - 0.25) <  epsilon);

    double c3 = clustering.clusteringCoefficient(g, Vertex::Degree(3));
    ASSERT_TRUE(fabs(c3 - 1) <  epsilon);
}

TEST_F(WeightedClusterCoefficientTest, AcyclicWeightedGraphTest)
{
    WeightedGraph ig;

    Vertex* x = new Vertex(1);
    Vertex* v1 = new Vertex(2);
    Vertex* v2 = new Vertex(3);
    Vertex* v3 = new Vertex(4);
    Vertex* v4 = new Vertex(5);

    ig.addVertex(x);
    ig.addVertex(v1);
    ig.addVertex(v2);
    ig.addVertex(v3);
    ig.addVertex(v4);
    ig.addEdge(x, v1, 1);
    ig.addEdge(x, v2, 1);
    ig.addEdge(x, v3, 1);
    ig.addEdge(v4, x, 1);;

    WeightedClusteringCoefficient<WeightedGraph, Vertex> clustering;

    double c = clustering.vertexClusteringCoefficient(x);

    double epsilon = 0.001;

    ASSERT_TRUE(fabs(c - 0.0) <  epsilon);

    double c2 = clustering.clusteringCoefficient(ig, Vertex::Degree(4));
    ASSERT_TRUE(fabs(c2 - 0.0) <  epsilon);
}

TEST_F(WeightedClusterCoefficientTest, SingleNodeGraph)
{
    WeightedGraph ig;

    Vertex* x = new Vertex(1);

    ig.addVertex(x);

    WeightedClusteringCoefficient<WeightedGraph, Vertex> clustering;

    double c = clustering.vertexClusteringCoefficient(x);

    double epsilon = 0.001;

    ASSERT_TRUE(fabs(c - 0.0) <  epsilon);

    double c2 = clustering.clusteringCoefficient(ig, Vertex::Degree(4));
    ASSERT_TRUE(fabs(c2 - 0.0) <  epsilon);
}

}

