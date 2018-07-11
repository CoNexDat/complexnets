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

namespace weightedClusterCoefficientTest {

    using namespace graphpp;
    using namespace std;
    using ::testing::Test;

    class WeightedBetweennessTest : public Test {

    protected:

        WeightedBetweennessTest() {}

        virtual ~WeightedBetweennessTest() {}


        virtual void SetUp() {

        }

        virtual void TearDown() {

        }

    public:
        typedef WeightedVertexAspect<AdjacencyListVertex> Vertex;
        typedef AdjacencyListGraph<Vertex> Graph;
        typedef WeightedGraphAspect<Vertex, Graph> WeightedGraph;

    };

    TEST_F(WeightedBetweennessTest , WeightedBetweennessTest)
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

        WeightedBetweenness<WeightedGraph, Vertex> betweenness {g};

        auto it = betweenness.iterator();

        while (!it.end())
        {
            std::cout << "----------" << std::endl;
            std::cout << "Id" << std::endl;
            std::cout << it->first << std::endl;
            std::cout << "Betweenness" << std::endl;
            std::cout << it->second << std::endl;
            ++it;
        }
    }
}
