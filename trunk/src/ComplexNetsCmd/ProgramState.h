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
	void setErdosRenyiGraph(unsigned int n, float p);
	void setBarabasiAlbertGraph(unsigned int m_0, unsigned int m, unsigned int n);
	double betweenness(unsigned int vertex_id);
	void exportBetweennessVsDegree(string outputPath);
	double degreeDistribution(unsigned int vertex_id);
};

#endif