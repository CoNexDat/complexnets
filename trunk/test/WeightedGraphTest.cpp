
#include <gtest/gtest.h>
#include <set>
#include <vector>
#include <list>

#include "../complexnets/AdjacencyListVertex.h"
#include "../complexnets/AdjacencyListGraph.h"
#include "../complexnets/GraphExceptions.h"
#include "../complexnets/WeightedGraphAspect.h"
#include "../complexnets/WeightedVertexAspect.h"

namespace weightedAspectsTest
{
    
    using namespace graphpp;
    using namespace std;
    using ::testing::Test;
    
    class WeightedGraphTest : public Test
    {
        
        protected:
            
            WeightedGraphTest() { }
            
            virtual ~WeightedGraphTest () { }
            
            
            virtual void SetUp()
            {
                
            }
            
            virtual void TearDown()
            {
                
            }
        public:
            typedef WeightedVertexAspect<AdjacencyListVertex> Vertex;
            typedef AdjacencyListGraph<Vertex> IndexedGraph;
            typedef AdjacencyListGraph<Vertex, list<Vertex*> > ListGraph;
            typedef AdjacencyListGraph<Vertex, vector<Vertex*> > VectorGraph;
            typedef WeightedGraphAspect<Vertex, VectorGraph> WeightedGraph;
            
    };
    
    
    TEST_F(WeightedGraphTest, AddWeightedEdgeTest)
    {
        WeightedGraph ig;
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
        
        ig.addEdge(x, v1, 1);
        ig.addEdge(x, v2, 2);
        ig.addEdge(x, v3, 3);
        ig.addEdge(v1, v2, 4);
        ig.addEdge(x, v4, 5);

        delete x;
        delete v1;
        delete v2;
        delete v3;
    }
    
}

