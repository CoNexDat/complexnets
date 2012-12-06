#include "ProgramState.h"
#include "../ComplexNets/IGraphReader.h"
#include "../ComplexNets/GraphFactory.h"
#include "../ComplexNets/WeightedGraphFactory.h"

using namespace std;
using namespace graphpp;

// Date member function
void ProgramState::setWeighted(bool weighted) {
    this->weighted = weighted;
}

void ProgramState::readGraphFromFile(string path) {
	if (isWeighted()) {
		this->weightedGraph = new WeightedGraph(false, false);

    	IGraphFactory<WeightedGraph, WeightedVertex> *factory = new WeightedGraphFactory<WeightedGraph, WeightedVertex>();
        IGraphReader<WeightedGraph, WeightedVertex> *reader = factory->createGraphReader();
        reader->read(*getWeightedGraph(), path);

        delete reader;
        delete factory;
    } else {
    	this->graph = new Graph(false, false);

    	IGraphFactory<Graph, Vertex> *factory = new GraphFactory<Graph, Vertex>();
    	IGraphReader<Graph, Vertex> *reader = factory->createGraphReader();
		reader->read(*getGraph(), path);

		delete reader;
		delete factory;
    }
}

bool ProgramState::isWeighted() {
	return this->weighted;
}

WeightedGraph *ProgramState::getWeightedGraph() {
	return this->weightedGraph;
}

Graph *ProgramState::getGraph() {
	return this->graph;
}