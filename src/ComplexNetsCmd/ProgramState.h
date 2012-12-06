#ifndef PROGRAM_STATE_H
#define PROGRAM_STATE_H

#include "../ComplexNets/AdjacencyListGraph.h"
#include "../ComplexNets/WeightedVertexAspect.h"
#include "../ComplexNets/WeightedGraphAspect.h"

typedef graphpp::AdjacencyListVertex Vertex;
typedef graphpp::AdjacencyListGraph<Vertex> Graph;
typedef graphpp::WeightedVertexAspect<Vertex> WeightedVertex;
typedef graphpp::WeightedGraphAspect<WeightedVertex, graphpp::AdjacencyListGraph<WeightedVertex> > WeightedGraph;

class ProgramState {

private:
	bool isWeighted;
    WeightedGraph *weightedGraph;
    Graph *graph;

public:
	void setIsWeighted(bool isWeighted);
	void setWeightedGraph(WeightedGraph *weightedGraph);
	void setGraph(Graph *weightedGraph);

	bool getIsWeighted();
	WeightedGraph *getWeightedGraph();
	Graph *getGraph();
};

#endif