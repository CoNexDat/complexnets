#ifndef GRAPH_WRITER_H
#define GRAPH_WRITER_H

#include "typedefs.h"

using namespace std;

class GraphWriter {

public:
    void write(Graph *g, string outputPath);

private:
	list<int> visitedVertexes;
	bool vertexWasVisited(Vertex *vertex);

};

#endif
