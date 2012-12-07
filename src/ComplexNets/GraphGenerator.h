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

	Graph generateErdosRenyiGraph(unsigned int n, unsigned int p);

};

#endif