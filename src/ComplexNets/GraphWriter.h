// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

#ifndef GRAPH_WRITER_H
#define GRAPH_WRITER_H

#include "typedefs.h"

using namespace std;

class GraphWriter {

public:
    void writeGraph(Graph *graph, string outputPath);
    void writeWeightedGraph(WeightedGraph *WeightedGraph, string outputPath);

private:
	list<unsigned int> visitedVertexes;
	bool vertexWasVisited(unsigned int vertexId);

};

#endif
