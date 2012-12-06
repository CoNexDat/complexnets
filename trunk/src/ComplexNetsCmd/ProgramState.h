#ifndef PROGRAM_STATE_H
#define PROGRAM_STATE_H

#include "../ComplexNets/AdjacencyListGraph.h"
#include "../ComplexNets/WeightedVertexAspect.h"
#include "../ComplexNets/WeightedGraphAspect.h"

typedef graphpp::AdjacencyListVertex Vertex;
typedef graphpp::AdjacencyListGraph<Vertex> Graph;
typedef graphpp::WeightedVertexAspect<Vertex> WeightedVertex;
typedef graphpp::WeightedGraphAspect<WeightedVertex, graphpp::AdjacencyListGraph<WeightedVertex> > WeightedGraph;

using namespace std;

class ProgramState {

private:
	bool weighted;
    WeightedGraph *weightedGraph;
    Graph *graph;

public:
	void setWeighted(bool weighted);
	void readGraphFromFile(string path);

	bool isWeighted();
	WeightedGraph *getWeightedGraph();
	Graph *getGraph();
};

#endif