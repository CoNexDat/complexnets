#include "GraphGenerator.h"
#include "../ComplexNets/IGraphReader.h"
#include "../ComplexNets/GraphFactory.h"
#include "../ComplexNets/WeightedGraphFactory.h"

using namespace graphpp;

GraphGenerator *GraphGenerator::instance = NULL;

GraphGenerator::GraphGenerator() {};

GraphGenerator *GraphGenerator::getInstance() {
	if (instance == NULL) {
		instance = new GraphGenerator();
	}

	return instance;
}


Graph GraphGenerator::generateGraphFromFile(string path, bool directed, bool multigraph) {
	Graph graph = Graph(directed, multigraph);

   	IGraphFactory<Graph, Vertex> *factory = new GraphFactory<Graph, Vertex>();
    IGraphReader<Graph, Vertex> *reader = factory->createGraphReader();
	reader->read(graph, path);

	delete reader;
	delete factory;

	return graph;
}


WeightedGraph GraphGenerator::generateWeightedGraphFromFile(string path, bool directed, bool multigraph) {
	WeightedGraph graph = WeightedGraph(directed, multigraph);

   	IGraphFactory<WeightedGraph, WeightedVertex> *factory = new WeightedGraphFactory<WeightedGraph, WeightedVertex>();
    IGraphReader<WeightedGraph, WeightedVertex> *reader = factory->createGraphReader();
    reader->read(graph, path);

	delete reader;
	delete factory;

	return graph;
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