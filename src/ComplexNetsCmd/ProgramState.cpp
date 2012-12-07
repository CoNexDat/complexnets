#include "ProgramState.h"
#include "../ComplexNets/GraphGenerator.h"

using namespace std;
using namespace graphpp;


void ProgramState::setWeighted(bool weighted) {
    this->weighted = weighted;
}

bool ProgramState::isWeighted() {
	return this->weighted;
}

WeightedGraph ProgramState::getWeightedGraph() {
	return this->weightedGraph;
}

Graph ProgramState::getGraph() {
	return this->graph;
}

void ProgramState::readGraphFromFile(string path) {
	if (isWeighted()) {
		this->weightedGraph = GraphGenerator::getInstance()->generateWeightedGraphFromFile(path, false, false);
    } else {
    	this->graph = GraphGenerator::getInstance()->generateGraphFromFile(path, false, false);
    }
}

void ProgramState::setErdosRenyiGraph(int n, float p) {

}