#include "GraphGenerator.h"

GraphGenerator *GraphGenerator::instance = NULL;

GraphGenerator::GraphGenerator() {};

GraphGenerator *GraphGenerator::getInstance() {
	if (instance == NULL) {
		instance = new GraphGenerator();
	}

	return instance;
}

Graph GraphGenerator::generateErdosRenyiGraph(unsigned int n, unsigned int p) {
	Graph graph = new Graph(false, false);

	for (unsigned int i = 1; i <= n; i++) {
		graph.addVertex(new Vertex(i));
	}

	for (unsigned int i = 1; i < n; i++) {
		Vertex* srcVertex = graph.getVertexById(i);

		for (unsigned int j = i + 1; j <= n; j++) {
			Vertex* destVertex = graph.getVertexById(j);

			if ((float) rand() / RAND_MAX <= p) {
				graph.addEdge(srcVertex, destVertex);
			}
		}
	}

	return graph;
}