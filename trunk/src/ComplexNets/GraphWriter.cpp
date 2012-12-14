#include <fstream>
#include <list>

#include "GraphWriter.h"
#include "AdjacencyListGraph.h"

using namespace std;
using namespace graphpp;

bool GraphWriter::vertexWasVisited(Vertex *vertex) {
	list<int>::iterator it = find(this->visitedVertexes.begin(), this->visitedVertexes.end(), vertex->getVertexId());

	return it != this->visitedVertexes.end();
}

void GraphWriter::write(Graph *g, string outputPath) {
    ofstream destinationFile;
    destinationFile.open(outputPath.c_str(), ios_base::out);

    this->visitedVertexes.clear();

    Graph::VerticesIterator verticesIterator = g->verticesIterator();
    

    while (!verticesIterator.end()) {
    	Vertex *vertex = *verticesIterator;
    	
    	Vertex::VerticesIterator neighborsIterator = vertex->neighborsIterator();

    	while (!neighborsIterator.end()) {
    		Vertex *neighbor = *neighborsIterator;

    		if (!vertexWasVisited(neighbor)) {
    			destinationFile << vertex->getVertexId() << " " << neighbor->getVertexId() << std::endl;
    		}
    		
    		neighborsIterator++;
    	}

    	this->visitedVertexes.push_back(vertex->getVertexId());
    	verticesIterator++;
    }

    destinationFile.close();
}