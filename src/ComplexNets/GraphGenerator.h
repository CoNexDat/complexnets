#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H

#include "../ComplexNets/typedefs.h"

using namespace std;

class GraphGenerator {

private:
	GraphGenerator();
	static GraphGenerator *instance;
	float distanceBetweenVertex(unsigned int vertex1Id, unsigned int vertex2Id);
	void addVertexPosition();
	int openDegrees(Vertex* vertex);
	void printVertexVector(Graph *graph, vector<unsigned int> vec);
	
public:
	static GraphGenerator *getInstance();

	Graph *generateGraphFromFile(string path, bool directed, bool multigraph);
	WeightedGraph *generateWeightedGraphFromFile(string path, bool directed, bool multigraph);
	Graph* generateErdosRenyiGraph(unsigned int n, float p);
	Graph* generateBarabasiAlbertGraph(unsigned int m_0, unsigned int m, unsigned int n);
	Graph* generateHotExtendedGraph(unsigned int m, unsigned int n, float xi, unsigned int q, float r);
	Graph* generateMolloyReedGraph(unsigned int k[]);
};

#endif
