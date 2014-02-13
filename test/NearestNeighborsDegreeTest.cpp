
#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <list>

#include "../src/ComplexNets/AdjacencyListVertex.h"
#include "../src/ComplexNets/AdjacencyListGraph.h"
#include "../src/ComplexNets/GraphExceptions.h"
#include "../src/ComplexNets/NearestNeighborsDegree.h"
#include "../src/ComplexNets/GraphReader.h"

namespace nearestNeighborsDegreeTest
{

using namespace graphpp;
using namespace std;
using ::testing::Test;

class NearestNeighborsDegreeTest : public Test
{

protected:

    NearestNeighborsDegreeTest() { }

    virtual ~NearestNeighborsDegreeTest() { }


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


TEST_F(NearestNeighborsDegreeTest , VertexGeneralTest)
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

    typedef NearestNeighborsDegree<ListGraph, Vertex> Knn;
    typedef Knn::MeanDegree MeanDegree;
    Knn knn;

    MeanDegree dx = knn.meanDegreeForVertex(x);
    MeanDegree dv1 = knn.meanDegreeForVertex(v1);
    MeanDegree dv4 = knn.meanDegreeForVertex(v4);


    MeanDegree epsilon = 0.001;

    ASSERT_TRUE(fabs(dx - 1.5) <  epsilon);
    ASSERT_TRUE(fabs(dv1 - 3) <  epsilon);
    ASSERT_TRUE(fabs(dv4 - 4) <  epsilon);

    MeanDegree meanDegree2 = knn.meanDegree(ig, Vertex::Degree(2));
    ASSERT_TRUE(fabs(meanDegree2 - 3.0) <  epsilon);
}

TEST_F(NearestNeighborsDegreeTest, RealWorldTest)
{
    VectorGraph * g = new VectorGraph(false, true);
    GraphReader<VectorGraph, Vertex> graphReader;

    graphReader.read(*g, "TestTrees/AS_CAIDA_2008.txt");

    Vertex * x = g->getVertexById(3);

    typedef NearestNeighborsDegree<ListGraph, Vertex> Knn;
    typedef Knn::MeanDegree MeanDegree;
    Knn knn;

    MeanDegree epsilon = 0.0001;

    MeanDegree dx = knn.meanDegreeForVertex(x);
    ASSERT_TRUE(fabs(dx - 651.25) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(701));
    ASSERT_TRUE(fabs(dx - 24.77924) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(702));
    ASSERT_TRUE(fabs(dx - 47.63469) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(1224));
    ASSERT_TRUE(fabs(dx - 38.0) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(2497));
    ASSERT_TRUE(fabs(dx - 85.65546) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(2907));
    ASSERT_TRUE(fabs(dx - 48.57377) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(3320));
    ASSERT_TRUE(fabs(dx - 55.16172) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(3561));
    ASSERT_TRUE(fabs(dx - 61.65812) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(3662));
    ASSERT_TRUE(fabs(dx - 81.41176) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(4780));
    ASSERT_TRUE(fabs(dx - 274.12) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(4837));
    ASSERT_TRUE(fabs(dx - 181.1892) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(5089));
    ASSERT_TRUE(fabs(dx - 285.2) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(5400));
    ASSERT_TRUE(fabs(dx - 100.5556) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(5459));
    ASSERT_TRUE(fabs(dx - 58.39631) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(5486));
    ASSERT_TRUE(fabs(dx - 288.7692) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(6325));
    ASSERT_TRUE(fabs(dx - 200.9744) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(6509));
    ASSERT_TRUE(fabs(dx - 70.84906) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(6714));
    ASSERT_TRUE(fabs(dx - 159.6429) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(7132));
    ASSERT_TRUE(fabs(dx - 62.96833) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(7228));
    ASSERT_TRUE(fabs(dx - 244.48) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(24093));
    ASSERT_TRUE(fabs(dx - 86.0) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(24112));
    ASSERT_TRUE(fabs(dx - 31.5) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(24130));
    ASSERT_TRUE(fabs(dx - 168.0) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(24399));
    ASSERT_TRUE(fabs(dx - 61.5) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(24479));
    ASSERT_TRUE(fabs(dx - 50.0) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(38220));
    ASSERT_TRUE(fabs(dx - 80.0) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(4635));
    ASSERT_TRUE(fabs(dx - 110.0851) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(4717));
    ASSERT_TRUE(fabs(dx - 54.48) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(714));
    ASSERT_TRUE(fabs(dx - 507.5) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(2110));
    ASSERT_TRUE(fabs(dx - 265.75) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(719));
    ASSERT_TRUE(fabs(dx - 9.0) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(790));
    ASSERT_TRUE(fabs(dx - 109.8571) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(3336));
    ASSERT_TRUE(fabs(dx - 10.0) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(21348));
    ASSERT_TRUE(fabs(dx - 4.5) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(760));
    ASSERT_TRUE(fabs(dx - 18.0) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(1853));
    ASSERT_TRUE(fabs(dx - 119.1111) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(766));
    ASSERT_TRUE(fabs(dx - 364.8) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(13041));
    ASSERT_TRUE(fabs(dx - 4.666667) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(15630));
    ASSERT_TRUE(fabs(dx - 9.5) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(1213));
    ASSERT_TRUE(fabs(dx - 202.75) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(2818));
    ASSERT_TRUE(fabs(dx - 370.1429) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(3213));
    ASSERT_TRUE(fabs(dx - 404.7143) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(5578));
    ASSERT_TRUE(fabs(dx - 227.0) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(6908));
    ASSERT_TRUE(fabs(dx - 155.0417) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(8546));
    ASSERT_TRUE(fabs(dx - 326.8571) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(29212));
    ASSERT_TRUE(fabs(dx - 38.0) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(34798));
    ASSERT_TRUE(fabs(dx - 25.0) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(789));
    ASSERT_TRUE(fabs(dx - 633.5) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(2609));
    ASSERT_TRUE(fabs(dx - 88.16667) <  epsilon);

    dx = knn.meanDegreeForVertex(g->getVertexById(5515));
    ASSERT_TRUE(fabs(dx - 83.5) <  epsilon);
}


}

