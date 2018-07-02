//
// Created by agop on 01/07/18.
//


#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <list>

#include "DirectedClusteringCoefficient.h"
#include "DirectedVertexAspect.h"
#include "AdjacencyListVertex.h"
#include "AdjacencyListGraph.h"

namespace directedClusteringCoefficientTest {

    using namespace graphpp;
    using namespace std;
    using ::testing::Test;

    class DirectedClusteringCoefficientTest : public Test {

    protected:

        DirectedClusteringCoefficientTest() {}

        virtual ~DirectedClusteringCoefficientTest() {}


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

    TEST_F(DirectedClusteringCoefficientTest , DirectedAdjacentTest) {
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
        ig.addEdge(x, v4);
        ig.addEdge(v3, x);
        ig.addEdge(v3, v4);

        DirectedClusteringCoefficient<ListGraph, DirectedVertex> clustering;

        ASSERT_TRUE(clustering.isDirectedAdjacent(x, v1));
        ASSERT_TRUE(clustering.isDirectedAdjacent(x, v2));
        ASSERT_TRUE(clustering.isDirectedAdjacent(x, v4));
        ASSERT_TRUE(clustering.isDirectedAdjacent(v3, x));
        ASSERT_TRUE(clustering.isDirectedAdjacent(v3, v4));
        
    }
}
