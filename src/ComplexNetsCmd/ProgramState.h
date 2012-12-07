#ifndef PROGRAM_STATE_H
#define PROGRAM_STATE_H

#include "../ComplexNets/typedefs.h"

using namespace std;

class ProgramState {

private:
	bool weighted;
    WeightedGraph weightedGraph;
    Graph graph;

public:
	void setWeighted(bool weighted);

	bool isWeighted();
	WeightedGraph getWeightedGraph();
	Graph getGraph();

	void readGraphFromFile(string path);
	void setErdosRenyiGraph(int n, float p);
};

#endif