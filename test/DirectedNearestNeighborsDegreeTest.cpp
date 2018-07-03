//
// Created by agop on 03/07/18.
//

#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <list>
#include <src/core/inc/typedefs.h>

#include "DirectedNearestNeighborsDegree.h"
#include "DirectedVertexAspect.h"
#include "AdjacencyListVertex.h"
#include "AdjacencyListGraph.h"

namespace directedNearestNeighborsDegreeTest {

    using namespace graphpp;
    using namespace std;
    using ::testing::Test;

    class DirectedNearestNeighborsDegreeTest : public Test {

    protected:

        DirectedNearestNeighborsDegreeTest() {}

        virtual ~DirectedNearestNeighborsDegreeTest() {}


        virtual void SetUp() {

        }

        virtual void TearDown() {

        }

    public:
        typedef DirectedVertexAspect<Vertex> DirectedVertex;

        typedef AdjacencyListGraph<DirectedVertex> IndexedGraph;
        typedef AdjacencyListGraph<DirectedVertex, list<DirectedVertex*> > ListGraph;
        typedef AdjacencyListGraph<DirectedVertex, vector<DirectedVertex*> > VectorGraph;
    };

    TEST_F(DirectedNearestNeighborsDegreeTest , DirectedNearestNeighborsDegreeTest) {
        ListGraph ig(true,false);
        //Create vertex
        DirectedVertex* x = new DirectedVertex(1);

        //create neighbor vertices
        DirectedVertex* v1 = new DirectedVertex(2);
        DirectedVertex* v2 = new DirectedVertex(3);
        DirectedVertex* v3 = new DirectedVertex(4);
        DirectedVertex* v4 = new DirectedVertex(5);

        ig.addVertex(x);
        ig.addVertex(v1);
        ig.addVertex(v2);
        ig.addVertex(v3);
        ig.addVertex(v4);

        ig.addEdge(x, v1);
        ig.addEdge(x, v2);
        ig.addEdge(x, v3);
        ig.addEdge(v2, v1);
        ig.addEdge(v4, x);

        typedef DirectedNearestNeighborsDegree<ListGraph, Vertex> Knn;
        Knn knn;

        double dx = knn.meanDegreeForVertex(x, true, true);
        double dv4 = knn.meanDegreeForVertex(v4, true, true);

        ASSERT_TRUE(dx == 0.25);
        ASSERT_TRUE(dv4 == 3);


        double epsilon = 0.001;

        double meanDegree2 = knn.meanDegree(ig, Vertex::Degree(1), true, true);
        ASSERT_TRUE(meanDegree2 == 1.75);

    }
}
