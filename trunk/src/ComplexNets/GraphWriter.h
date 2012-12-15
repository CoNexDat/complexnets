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
