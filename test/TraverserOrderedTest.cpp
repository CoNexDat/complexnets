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
#include "ComplexNets/TraverserOrdered.h"

namespace traverserOrderedTest
{

using namespace graphpp;
using namespace std;
using ::testing::Test;

class TraverserOrderedTest : public Test
{

protected:

    TraverserOrderedTest() { }

    virtual ~TraverserOrderedTest() { }


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

class DegreeCompare{
public:
    bool operator()(const Vertex* v1, const Vertex* v2){
        return v1->degree() > v2->degree();
    }
};

TEST_F(TraverserOrderedTest, TraverseOrderedIndexedTest)
{
    IndexedGraph ig;
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
    ig.addEdge(v1, v4);


    KeepTrackVisitor visitor;

    TraverserOrdered<IndexedGraph, Vertex, KeepTrackVisitor,DegreeCompare >::traverse(ig, visitor,DegreeCompare());

    ASSERT_EQ(visitor.visits.count(1), 1);
    ASSERT_EQ(visitor.visits.count(2), 1);
    ASSERT_EQ(visitor.visits.count(3), 1);
    ASSERT_EQ(visitor.visits.count(4), 1);
    ASSERT_EQ(visitor.visits.count(5), 1);
    ASSERT_EQ(visitor.visits.count(6), 0);
}

TEST_F(TraverserOrderedTest, TraverseOrderedListTest)
{
    ListGraph ig;
    
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
    ig.addEdge(v1, v4);


    KeepTrackVisitor visitor;

    TraverserOrdered<ListGraph, Vertex, KeepTrackVisitor,DegreeCompare >::traverse(ig, visitor,DegreeCompare());


    ASSERT_EQ(visitor.visits.count(1), 1);
    ASSERT_EQ(visitor.visits.count(2), 1);
    ASSERT_EQ(visitor.visits.count(3), 1);
    ASSERT_EQ(visitor.visits.count(4), 1);
    ASSERT_EQ(visitor.visits.count(5), 1);
    ASSERT_EQ(visitor.visits.count(6), 0);
}
TEST_F(TraverserOrderedTest, TraverserOrderedVectorTest)
{
    VectorGraph ig;
    
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
    ig.addEdge(v1, v4);


    KeepTrackVisitor visitor;

    TraverserOrdered<VectorGraph, Vertex, KeepTrackVisitor,DegreeCompare >::traverse(ig, visitor,DegreeCompare());


    ASSERT_EQ(visitor.visits.count(1), 1);
    ASSERT_EQ(visitor.visits.count(2), 1);
    ASSERT_EQ(visitor.visits.count(3), 1);
    ASSERT_EQ(visitor.visits.count(4), 1);
    ASSERT_EQ(visitor.visits.count(5), 1);
    ASSERT_EQ(visitor.visits.count(6), 0);
}
}
