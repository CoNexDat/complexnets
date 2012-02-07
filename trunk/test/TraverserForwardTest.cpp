
#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <list>

#include "../src/ComplexNets/AdjacencyListVertex.h"
#include "../src/ComplexNets/AdjacencyListGraph.h"
#include "../src/ComplexNets/GraphExceptions.h"
#include "../src/ComplexNets/TraverserForward.h"

namespace traverserForwardTest
{

using namespace graphpp;
using namespace std;
using ::testing::Test;

class TraverserForwardTest : public Test
{

protected:

    TraverserForwardTest() { }

    virtual ~TraverserForwardTest() { }


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

struct KeepTrackVisitor
{

    bool visitVertex(TraverserForwardTest::Vertex* v)
    {
        visits.insert(v->getVertexId());
        return true;
    }

    std::set<TraverserForwardTest::Vertex::VertexId> visits;
};

TEST_F(TraverserForwardTest, TraverseForwardIndexedTest)
{
    TraverserForwardTest::IndexedGraph ig;
    //Create vertex
    TraverserForwardTest::Vertex* x = new TraverserForwardTest::Vertex(1);

    //create neighbor vertices
    TraverserForwardTest::Vertex* v1 = new TraverserForwardTest::Vertex(2);
    TraverserForwardTest::Vertex* v2 = new TraverserForwardTest::Vertex(3);
    TraverserForwardTest::Vertex* v3 = new TraverserForwardTest::Vertex(4);

    ig.addVertex(x);
    ig.addVertex(v1);
    ig.addVertex(v2);
    ig.addVertex(v3);

    KeepTrackVisitor visitor;

    TraverserForward<TraverserForwardTest::IndexedGraph, TraverserForwardTest::Vertex, KeepTrackVisitor>::traverse(ig, visitor);

    ASSERT_EQ(visitor.visits.count(1), 1);
    ASSERT_EQ(visitor.visits.count(2), 1);
    ASSERT_EQ(visitor.visits.count(3), 1);
    ASSERT_EQ(visitor.visits.count(4), 1);
    ASSERT_EQ(visitor.visits.count(5), 0);
}

TEST_F(TraverserForwardTest, TraverseForwardIndexedIteratorTest)
{
    TraverserForwardTest::IndexedGraph ig;
    //Create vertex
    TraverserForwardTest::Vertex* x = new TraverserForwardTest::Vertex(1);

    //create neighbor vertices
    TraverserForwardTest::Vertex* v1 = new TraverserForwardTest::Vertex(2);
    TraverserForwardTest::Vertex* v2 = new TraverserForwardTest::Vertex(3);
    TraverserForwardTest::Vertex* v3 = new TraverserForwardTest::Vertex(4);

    ig.addVertex(x);
    ig.addVertex(v1);
    ig.addVertex(v2);
    ig.addVertex(v3);

    KeepTrackVisitor visitor;
    //this time, traverse from the iterator to the second element
    IndexedGraph::VerticesIterator it = ig.verticesIterator();
    Vertex::VertexId excluded = (*it)->getVertexId();
    ++it;

    TraverserForward<IndexedGraph, Vertex, KeepTrackVisitor>::traverse(it, visitor);

    ASSERT_EQ(visitor.visits.count(1), excluded == 1 ? 0 : 1);
    ASSERT_EQ(visitor.visits.count(2), excluded == 2 ? 0 : 1);
    ASSERT_EQ(visitor.visits.count(3), excluded == 3 ? 0 : 1);
    ASSERT_EQ(visitor.visits.count(4), excluded == 4 ? 0 : 1);
    ASSERT_EQ(visitor.visits.count(5), 0);
}

TEST_F(TraverserForwardTest, TraverseForwardListTest)
{
    TraverserForwardTest::ListGraph ig;
    //Create vertex
    TraverserForwardTest::Vertex* x = new TraverserForwardTest::Vertex(1);

    //create neighbor vertices
    TraverserForwardTest::Vertex* v1 = new TraverserForwardTest::Vertex(2);
    TraverserForwardTest::Vertex* v2 = new TraverserForwardTest::Vertex(3);
    TraverserForwardTest::Vertex* v3 = new TraverserForwardTest::Vertex(4);

    ig.addVertex(x);
    ig.addVertex(v1);
    ig.addVertex(v2);
    ig.addVertex(v3);

    KeepTrackVisitor visitor;

    TraverserForward<TraverserForwardTest::ListGraph, TraverserForwardTest::Vertex, KeepTrackVisitor>::traverse(ig, visitor);

    ASSERT_EQ(visitor.visits.count(1), 1);
    ASSERT_EQ(visitor.visits.count(2), 1);
    ASSERT_EQ(visitor.visits.count(3), 1);
    ASSERT_EQ(visitor.visits.count(4), 1);
    ASSERT_EQ(visitor.visits.count(5), 0);
}

TEST_F(TraverserForwardTest, TraverseForwardListIteratorTest)
{
    TraverserForwardTest::ListGraph ig;
    //Create vertex
    TraverserForwardTest::Vertex* x = new TraverserForwardTest::Vertex(1);

    //create neighbor vertices
    TraverserForwardTest::Vertex* v1 = new TraverserForwardTest::Vertex(2);
    TraverserForwardTest::Vertex* v2 = new TraverserForwardTest::Vertex(3);
    TraverserForwardTest::Vertex* v3 = new TraverserForwardTest::Vertex(4);

    ig.addVertex(x);
    ig.addVertex(v1);
    ig.addVertex(v2);
    ig.addVertex(v3);

    KeepTrackVisitor visitor;
    //this time, traverse from the iterator to the second element
    ListGraph::VerticesIterator it = ig.verticesIterator();
    Vertex::VertexId excluded = (*it)->getVertexId();
    ++it;

    TraverserForward<ListGraph, Vertex, KeepTrackVisitor>::traverse(it, visitor);

    ASSERT_EQ(visitor.visits.count(1), excluded == 1 ? 0 : 1);
    ASSERT_EQ(visitor.visits.count(2), excluded == 2 ? 0 : 1);
    ASSERT_EQ(visitor.visits.count(3), excluded == 3 ? 0 : 1);
    ASSERT_EQ(visitor.visits.count(4), excluded == 4 ? 0 : 1);
    ASSERT_EQ(visitor.visits.count(5), 0);
}

TEST_F(TraverserForwardTest, TraverseForwardVectorTest)
{
    TraverserForwardTest::VectorGraph ig;
    //Create vertex
    TraverserForwardTest::Vertex* x = new TraverserForwardTest::Vertex(1);

    //create neighbor vertices
    TraverserForwardTest::Vertex* v1 = new TraverserForwardTest::Vertex(2);
    TraverserForwardTest::Vertex* v2 = new TraverserForwardTest::Vertex(3);
    TraverserForwardTest::Vertex* v3 = new TraverserForwardTest::Vertex(4);

    ig.addVertex(x);
    ig.addVertex(v1);
    ig.addVertex(v2);
    ig.addVertex(v3);

    KeepTrackVisitor visitor;

    TraverserForward<TraverserForwardTest::VectorGraph, TraverserForwardTest::Vertex, KeepTrackVisitor>::traverse(ig, visitor);

    ASSERT_EQ(visitor.visits.count(1), 1);
    ASSERT_EQ(visitor.visits.count(2), 1);
    ASSERT_EQ(visitor.visits.count(3), 1);
    ASSERT_EQ(visitor.visits.count(4), 1);
    ASSERT_EQ(visitor.visits.count(5), 0);
}

TEST_F(TraverserForwardTest, TraverseForwardVectorIteratorTest)
{
    TraverserForwardTest::VectorGraph ig;
    //Create vertex
    TraverserForwardTest::Vertex* x = new TraverserForwardTest::Vertex(1);

    //create neighbor vertices
    TraverserForwardTest::Vertex* v1 = new TraverserForwardTest::Vertex(2);
    TraverserForwardTest::Vertex* v2 = new TraverserForwardTest::Vertex(3);
    TraverserForwardTest::Vertex* v3 = new TraverserForwardTest::Vertex(4);

    ig.addVertex(x);
    ig.addVertex(v1);
    ig.addVertex(v2);
    ig.addVertex(v3);

    KeepTrackVisitor visitor;
    //this time, traverse from the iterator to the second element
    VectorGraph::VerticesIterator it = ig.verticesIterator();
    Vertex::VertexId excluded = (*it)->getVertexId();
    ++it;

    TraverserForward<VectorGraph, Vertex, KeepTrackVisitor>::traverse(it, visitor);

    ASSERT_EQ(visitor.visits.count(1), excluded == 1 ? 0 : 1);
    ASSERT_EQ(visitor.visits.count(2), excluded == 2 ? 0 : 1);
    ASSERT_EQ(visitor.visits.count(3), excluded == 3 ? 0 : 1);
    ASSERT_EQ(visitor.visits.count(4), excluded == 4 ? 0 : 1);
    ASSERT_EQ(visitor.visits.count(5), 0);
}

}

