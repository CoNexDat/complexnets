//
// Created by agop.
//

//
// Created by agop
//

#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <list>

#include "AdjacencyListVertex.h"
#include "AdjacencyListGraph.h"
#include "GraphExceptions.h"
#include "WeightedGraphAspect.h"
#include "WeightedVertexAspect.h"
#include "WeightedBetweenness.h"

namespace weightedGraphTest {

    using namespace graphpp;
    using namespace std;
    using ::testing::Test;

    class WeightedGraphTest : public Test {

    protected:

        WeightedGraphTest() {}

        virtual ~WeightedGraphTest() {}


        virtual void SetUp() {

        }

        virtual void TearDown() {

        }

    public:
        typedef WeightedVertexAspect<AdjacencyListVertex> Vertex;
        typedef AdjacencyListGraph<Vertex> Graph;
        typedef WeightedGraphAspect<Vertex, Graph> WeightedGraph;

    };

    TEST_F(WeightedGraphTest , WeightedGraphTest)
    {
        WeightedGraph g;
        //Create vertex
        Vertex* x = new Vertex(1);

        //create neighbor vertices
        Vertex* v1 = new Vertex(2);
        Vertex* v2 = new Vertex(3);
        Vertex* v3 = new Vertex(4);
        Vertex* v4 = new Vertex(5);
        Vertex* v5 = new Vertex(6);

        g.addVertex(x);
        g.addVertex(v1);
        g.addVertex(v2);
        g.addVertex(v3);
        g.addVertex(v4);
        g.addVertex(v5);

        g.addEdge(x, v1, 4);
        g.addEdge(x, v2, 1);
        g.addEdge(x, v3, 4);
        g.addEdge(x, v4, 2);
        g.addEdge(v1, v2, 2);
        g.addEdge(v4, v5, 1);

        ASSERT_TRUE(x->edgeWeight(v1) == 4);
        ASSERT_TRUE(x->edgeWeight(v2) == 1);
        ASSERT_TRUE(x->edgeWeight(v3) == 4);
        ASSERT_TRUE(v1->edgeWeight(v2) == 2);
        ASSERT_TRUE(x->edgeWeight(v4) == 2);
        ASSERT_TRUE(v4->edgeWeight(v5) == 1);
    }
}
