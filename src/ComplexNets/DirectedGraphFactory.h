#ifndef DIRECTED_GRAPH_FACTORY_H
#define DIRECTED_GRAPH_FACTORY_H

#include "IGraphFactory.h"
#include "DirectedDegreeDistribution.h"
#include "GraphReader.h"

namespace graphpp
{
template<class Graph, class Vertex>
class DirectedGraphFactory: public IGraphFactory<Graph, Vertex>
{
    virtual IGraphReader<Graph, Vertex>* createGraphReader()
    {
        return new GraphReader<Graph, Vertex>();
    }
    virtual IBetweenness<Graph, Vertex>* createBetweenness(Graph&)
    {
		//TODO Implement this
        //return new DirectedBetweenness<Graph,Vertex>();
        return NULL;
    }
    virtual IClusteringCoefficient<Graph, Vertex>* createClusteringCoefficient()
    {
		//TODO Implement this
        //return new DirectedClusteringCoefficient<Graph,Vertex>();
        return NULL;
	}
    virtual INearestNeighborsDegree<Graph, Vertex>* createNearestNeighborsDegree()
    {
		//TODO Implement this
        //return new DirectedNearestNeighborsDegree<Graph,Vertex>();
        return NULL;
    }
    virtual IShellIndex<Graph, Vertex>* createShellIndex(Graph&)
    {
		//TODO Implement this
        //return new DirectedShellIndex<Graph,Vertex>();
        return NULL;
    }
    virtual IDegreeDistribution<Graph, Vertex>* createDegreeDistribution(Graph& g)
    {
        return new DirectedDegreeDistribution<Graph, Vertex>(g);
    }
    
    virtual MaxClique<Graph, Vertex>* createMaxClique(Graph&)
    {
        return NULL;
    }
        
    virtual MaxCliqueExact<Graph, Vertex>* createExactMaxClique(Graph&, int)
    {
        return NULL;
    }

    virtual StrengthDistribution<Graph, Vertex>* createStrengthDistribution(Graph& g)
    {
        return NULL;
    }
};
}

#endif

