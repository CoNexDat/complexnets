//
// Created by María de los Ángeles Arlanti on 07/07/18.
// Modified by ... on ../../..
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

namespace directedVertexTest {

    using namespace graphpp;
    using namespace std;
    using ::testing::Test;

    class DirectedVertexTest : public Test {

    protected:

        DirectedVertexTest() {}

        virtual ~DirectedVertexTest() {}


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

    TEST_F(DirectedVertexTest , DirectedVertexAddEdgeTest) {
        //Create vertex
        DirectedVertex* x = new DirectedVertex(1);

        //create neighbor vertex
        DirectedVertex* v1 = new DirectedVertex(2);

        x->addEdge(v1);

        ASSERT_EQ(x->outDegree(), 1);
        ASSERT_EQ(v1->inDegree(), 1);
    }

    TEST_F(DirectedVertexTest , DirectedVertexAddIncomingEdgeTest) {
        //Create vertex
        DirectedVertex* x = new DirectedVertex(1);

        //create neighbor vertex
        DirectedVertex* v1 = new DirectedVertex(2);

        x->addIncomingEdge(v1);

       ASSERT_EQ(v1->outDegree(), 1);
        ASSERT_EQ(x->inDegree(), 1);
    }
}