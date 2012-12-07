#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H

#include "../ComplexNets/typedefs.h"

using namespace std;

class GraphGenerator {

private:
	GraphGenerator();
	static GraphGenerator *instance;

public:
	static GraphGenerator *getInstance();

	Graph generateGraphFromFile(string path, bool directed, bool multigraph);
	WeightedGraph generateWeightedGraphFromFile(string path, bool directed, bool multigraph);
	Graph generateErdosRenyiGraph(unsigned int n, unsigned int p);

};

#endif