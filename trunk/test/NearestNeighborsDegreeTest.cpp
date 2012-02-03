
#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <list>

#include "../complexnets/AdjacencyListVertex.h"
#include "../complexnets/AdjacencyListGraph.h"
#include "../complexnets/GraphExceptions.h"
#include "../complexnets/NearestNeighborsDegree.h"

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

    MeanDegree dx = Knn::meanDegreeForVertex(x);
    MeanDegree dv1 = Knn::meanDegreeForVertex(v1);
    MeanDegree dv4 = Knn::meanDegreeForVertex(v4);


    MeanDegree epsilon = 0.001;

    ASSERT_TRUE(fabs(dx - 1.5) <  epsilon);
    ASSERT_TRUE(fabs(dv1 - 3) <  epsilon);
    ASSERT_TRUE(fabs(dv4 - 4) <  epsilon);

    MeanDegree meanDegree2 = Knn::meanDegree(ig, Vertex::Degree(2));
    ASSERT_TRUE(fabs(meanDegree2 - 3.0) <  epsilon);
}
}

