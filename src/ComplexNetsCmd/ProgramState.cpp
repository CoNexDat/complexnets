#include "ProgramState.h"

// Date member function
void ProgramState::setIsWeighted(bool isWeighted) {
    this->isWeighted = isWeighted;
}

void ProgramState::setWeightedGraph(WeightedGraph *weightedGraph) {
	this->weightedGraph = weightedGraph;
}

void ProgramState::setGraph(Graph *graph) {
	this->graph = graph;
}

bool ProgramState::getIsWeighted() {
	return this->isWeighted;
}

WeightedGraph *ProgramState::getWeightedGraph() {
	return this->weightedGraph;
}

Graph *ProgramState::getGraph() {
	return this->graph;
}