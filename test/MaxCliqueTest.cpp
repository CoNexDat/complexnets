//
// Created by agop.
//

#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <list>

#include "AdjacencyListVertex.h"
#include "AdjacencyListGraph.h"
#include "GraphExceptions.h"
#include "MaxClique.h"
#include "GraphReader.h"

namespace maxCliqueTest
{

    using namespace graphpp;
    using namespace std;
    using ::testing::Test;

    class MaxCliqueTest : public Test
    {

    protected:

        MaxCliqueTest() { }

        virtual ~MaxCliqueTest() { }


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


    TEST_F(MaxCliqueTest , MaxCliqueSizeTest) {
        ListGraph ig;
        //Create vertex
        Vertex *x = new Vertex(1);

        //create neighbor vertices
        Vertex *v1 = new Vertex(2);
        Vertex *v2 = new Vertex(3);
        Vertex *v3 = new Vertex(4);
        Vertex *v4 = new Vertex(5);

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

        MaxClique<ListGraph, Vertex> maxClique {ig};

        ASSERT_TRUE(maxClique.getMaxCliqueSize(x) == 3);
        ASSERT_TRUE(maxClique.getMaxCliqueSize(v1) == 3);
        ASSERT_TRUE(maxClique.getMaxCliqueSize(v2) == 3);
        ASSERT_TRUE(maxClique.getMaxCliqueSize(v3) == 2);
        ASSERT_TRUE(maxClique.getMaxCliqueSize(v4) == 2);

    }

    TEST_F(MaxCliqueTest , MaxCliqueListTest) {
        ListGraph ig;
        //Create vertex
        Vertex *x = new Vertex(1);

        //create neighbor vertices
        Vertex *v1 = new Vertex(2);
        Vertex *v2 = new Vertex(3);
        Vertex *v3 = new Vertex(4);
        Vertex *v4 = new Vertex(5);

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

        MaxClique<ListGraph, Vertex> maxClique {ig};

        std::list<int> list = maxClique.getMaxCliqueList();
        list.sort();
        std::list<int>::iterator it = list.begin();

        ASSERT_TRUE(*it == 1);
        std::advance(it, 1);
        ASSERT_TRUE(*it == 2);
        std::advance(it, 1);
        ASSERT_TRUE(*it == 3);

    }
}
