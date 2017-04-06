/**
 * 2do cuatrimestre 2014
 * @author  Luciana Reznik
 */
#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <list>

#include "ComplexNets/AdjacencyListVertex.h"
#include "ComplexNets/AdjacencyListGraph.h"
#include "ComplexNets/GraphExceptions.h"
#include "ComplexNets/typedefs.h"
#include "ComplexNets/TraverserBFS.h"

namespace traverserBFSTest
{

using namespace graphpp;
using namespace std;
using ::testing::Test;

class TraverserBFSTest : public Test
{

protected:

    TraverserBFSTest() { }

    virtual ~TraverserBFSTest() { }


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

    typedef  Graph::VerticesConstIterator VertexForwardIterator;
};

struct KeepTrackVisitor
{

    bool visitVertex(Vertex* v)
    {
        visits.insert(v->getVertexId());
        return true;
    }

    std::set<Vertex::VertexId> visits;
};

TEST_F(TraverserBFSTest, TraverseBFSIndexedTest)
{
    IndexedGraph ig;
    //Create vertex
    Vertex* x = new TraverserBFSTest::Vertex(1);

    //create neighbor vertices
    Vertex* v1 = new TraverserBFSTest::Vertex(2);
    Vertex* v2 = new TraverserBFSTest::Vertex(3);
    Vertex* v3 = new TraverserBFSTest::Vertex(4);
    Vertex* v4 = new TraverserBFSTest::Vertex(5);

    ig.addVertex(x);
    ig.addVertex(v1);
    ig.addVertex(v2);
    ig.addVertex(v3);
    ig.addVertex(v4);

    ig.addEdge(x, v1);
    ig.addEdge(x, v2);
    ig.addEdge(x, v3);
    ig.addEdge(v1, v2);
    ig.addEdge(v1, v4);


    KeepTrackVisitor visitor;
    
    VertexForwardIterator iter = ig.verticesConstIterator();
    
    Vertex* source = *iter;

    TraverserBFS<IndexedGraph, Vertex, KeepTrackVisitor>::traverse(source, visitor);        


    ASSERT_EQ(visitor.visits.count(1), 1);
    ASSERT_EQ(visitor.visits.count(2), 1);
    ASSERT_EQ(visitor.visits.count(3), 1);
    ASSERT_EQ(visitor.visits.count(4), 1);
    ASSERT_EQ(visitor.visits.count(5), 1);
    ASSERT_EQ(visitor.visits.count(6), 0);

}

TEST_F(TraverserBFSTest, TraverseBFSIndexedSourceTest)
{
    IndexedGraph ig;
    //Create vertex
    Vertex* x = new TraverserBFSTest::Vertex(1);

    //create neighbor vertices
    Vertex* v1 = new TraverserBFSTest::Vertex(2);
    Vertex* v2 = new TraverserBFSTest::Vertex(3);
    Vertex* v3 = new TraverserBFSTest::Vertex(4);
    Vertex* v4 = new TraverserBFSTest::Vertex(5);

    ig.addVertex(x);
    ig.addVertex(v1);
    ig.addVertex(v2);
    ig.addVertex(v3);
    ig.addVertex(v4);

    ig.addEdge(x, v1);
    ig.addEdge(x, v2);
    ig.addEdge(x, v3);
    ig.addEdge(v1, v2);
    ig.addEdge(v1, v4);

    KeepTrackVisitor visitor;
    //this time, traverse from the iterator to the second element

    VertexForwardIterator iter = ig.verticesConstIterator();
    ++iter;
    Vertex* source = *iter;

    TraverserBFS<IndexedGraph, Vertex, KeepTrackVisitor>::traverse(source, visitor);        

    ASSERT_EQ(visitor.visits.count(1), 1);
    ASSERT_EQ(visitor.visits.count(2), 1);
    ASSERT_EQ(visitor.visits.count(3), 1);
    ASSERT_EQ(visitor.visits.count(4), 1);
    ASSERT_EQ(visitor.visits.count(5), 1);
    ASSERT_EQ(visitor.visits.count(6), 0);
}
TEST_F(TraverserBFSTest, TraverseBFSListTest)
{
    ListGraph ig;
    
    //Create vertex
    Vertex* x = new TraverserBFSTest::Vertex(1);

    //create neighbor vertices
    Vertex* v1 = new TraverserBFSTest::Vertex(2);
    Vertex* v2 = new TraverserBFSTest::Vertex(3);
    Vertex* v3 = new TraverserBFSTest::Vertex(4);
    Vertex* v4 = new TraverserBFSTest::Vertex(5);

    ig.addVertex(x);
    ig.addVertex(v1);
    ig.addVertex(v2);
    ig.addVertex(v3);
    ig.addVertex(v4);

    ig.addEdge(x, v1);
    ig.addEdge(x, v2);
    ig.addEdge(x, v3);
    ig.addEdge(v1, v2);
    ig.addEdge(v1, v4);


    KeepTrackVisitor visitor;
    
    TraverserBFS<ListGraph, Vertex, KeepTrackVisitor>::traverse(x, visitor);        


    ASSERT_EQ(visitor.visits.count(1), 1);
    ASSERT_EQ(visitor.visits.count(2), 1);
    ASSERT_EQ(visitor.visits.count(3), 1);
    ASSERT_EQ(visitor.visits.count(4), 1);
    ASSERT_EQ(visitor.visits.count(5), 1);
    ASSERT_EQ(visitor.visits.count(6), 0);
}

TEST_F(TraverserBFSTest, TraverseBFSListSourceTest)
{
    ListGraph ig;
       //Create vertex
    Vertex* x = new TraverserBFSTest::Vertex(1);

    //create neighbor vertices
    Vertex* v1 = new TraverserBFSTest::Vertex(2);
    Vertex* v2 = new TraverserBFSTest::Vertex(3);
    Vertex* v3 = new TraverserBFSTest::Vertex(4);
    Vertex* v4 = new TraverserBFSTest::Vertex(5);

    ig.addVertex(x);
    ig.addVertex(v1);
    ig.addVertex(v2);
    ig.addVertex(v3);
    ig.addVertex(v4);

    ig.addEdge(x, v1);
    ig.addEdge(x, v2);
    ig.addEdge(x, v3);
    ig.addEdge(v1, v2);
    ig.addEdge(v1, v4);


    KeepTrackVisitor visitor;
    //this time, traverse from the iterator to the second element


    ListGraph::VerticesIterator it = ig.verticesIterator();
    Vertex::VertexId excluded = (*it)->getVertexId();
    ++it;
    Vertex* source = *it;

    TraverserBFS<ListGraph, Vertex, KeepTrackVisitor>::traverse(source, visitor);

    ASSERT_EQ(visitor.visits.count(1), 1);
    ASSERT_EQ(visitor.visits.count(2), 1);
    ASSERT_EQ(visitor.visits.count(3), 1);
    ASSERT_EQ(visitor.visits.count(4), 1);
    ASSERT_EQ(visitor.visits.count(5), 1);
    ASSERT_EQ(visitor.visits.count(6), 0);
}

TEST_F(TraverserBFSTest, TraverseBFSVectorTest)
{
    VectorGraph ig;
    //Create vertex
    Vertex* x = new TraverserBFSTest::Vertex(1);

    //create neighbor vertices
    Vertex* v1 = new TraverserBFSTest::Vertex(2);
    Vertex* v2 = new TraverserBFSTest::Vertex(3);
    Vertex* v3 = new TraverserBFSTest::Vertex(4);
    Vertex* v4 = new TraverserBFSTest::Vertex(5);

    ig.addVertex(x);
    ig.addVertex(v1);
    ig.addVertex(v2);
    ig.addVertex(v3);
    ig.addVertex(v4);

    ig.addEdge(x, v1);
    ig.addEdge(x, v2);
    ig.addEdge(x, v3);
    ig.addEdge(v1, v2);
    ig.addEdge(v1, v4);

    KeepTrackVisitor visitor;

    TraverserBFS<VectorGraph, Vertex, KeepTrackVisitor>::traverse(x, visitor);        

    ASSERT_EQ(visitor.visits.count(1), 1);
    ASSERT_EQ(visitor.visits.count(2), 1);
    ASSERT_EQ(visitor.visits.count(3), 1);
    ASSERT_EQ(visitor.visits.count(4), 1);
    ASSERT_EQ(visitor.visits.count(5), 1);
    ASSERT_EQ(visitor.visits.count(6), 0);
}

TEST_F(TraverserBFSTest, TraverseBFSVectorSourceTest)
{
    VectorGraph ig;
     //Create vertex
        //Create vertex
    Vertex* x = new TraverserBFSTest::Vertex(1);

    //create neighbor vertices
    Vertex* v1 = new TraverserBFSTest::Vertex(2);
    Vertex* v2 = new TraverserBFSTest::Vertex(3);
    Vertex* v3 = new TraverserBFSTest::Vertex(4);
    Vertex* v4 = new TraverserBFSTest::Vertex(5);

    ig.addVertex(x);
    ig.addVertex(v1);
    ig.addVertex(v2);
    ig.addVertex(v3);
    ig.addVertex(v4);

    ig.addEdge(x, v1);
    ig.addEdge(x, v2);
    ig.addEdge(x, v3);
    ig.addEdge(v1, v2);
    ig.addEdge(v1, v4);

    KeepTrackVisitor visitor;

    //this time, traverse from the iterator to the second element
    VectorGraph::VerticesIterator it = ig.verticesIterator();
    Vertex::VertexId excluded = (*it)->getVertexId();
    ++it;
    Vertex* source = *it;

    TraverserBFS<ListGraph, Vertex, KeepTrackVisitor>::traverse(source, visitor);

    ASSERT_EQ(visitor.visits.count(1), 1);
    ASSERT_EQ(visitor.visits.count(2), 1);
    ASSERT_EQ(visitor.visits.count(3), 1);
    ASSERT_EQ(visitor.visits.count(4), 1);
    ASSERT_EQ(visitor.visits.count(5), 1);
    ASSERT_EQ(visitor.visits.count(6), 0);
}


}

