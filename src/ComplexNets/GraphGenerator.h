// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

#ifndef GRAPH_GENERATOR_H
#define GRAPH_GENERATOR_H

#include "../ComplexNets/typedefs.h"
#include "../ComplexNets/MolloyReedGraphReader.h"

using namespace std;

class GraphGenerator {

private:
	typedef struct PolarPosition { double r; double theta; } PolarPosition;
	GraphGenerator();
	static GraphGenerator *instance;
	float distanceBetweenVertex(unsigned int vertex1Id, unsigned int vertex2Id);
	void addVertexPosition();	
	void addEdges(Graph* graph, Vertex* vertex, map<float, unsigned int> distance, unsigned int quant, vector<unsigned int>* vertexIndexes);
	inline double hiperbolicDistance(PolarPosition p1, PolarPosition p2);
	inline double getMaxRadius(int i, float a, float c);
	inline PolarPosition getRandomHyperbolicCoordinates( float a, double maxr );
public:
	static GraphGenerator *getInstance();

	Graph *generateGraphFromFile(string path, bool directed, bool multigraph);
	DirectedGraph *generateDirectedGraphFromFile(string path, bool multigraph);
	WeightedGraph *generateWeightedGraphFromFile(string path, bool directed, bool multigraph);
	Graph* generateErdosRenyiGraph(unsigned int n, float p);
	Graph* generateBarabasiAlbertGraph(unsigned int m_0, unsigned int m, unsigned int n);
	Graph* generateHotExtendedGraph(unsigned int m, unsigned int n, float xi, unsigned int q, float r, unsigned int t);
	Graph* generateMolloyReedGraph(string path);
	Graph* generateHiperbolicGraph(unsigned int n, float a, float c);
	double getExpectedAvgNodeDeg(unsigned int n, float a, float c);
};

#endif
