// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

#include <fstream>

#include "AdjacencyListGraph.h"
#include "GraphWriter.h"

using namespace graphpp;

bool GraphWriter::vertexWasVisited(unsigned int vertexId)
{
    std::list<unsigned int>::iterator it =
        find(this->visitedVertexes.begin(), this->visitedVertexes.end(), vertexId);
    return it != this->visitedVertexes.end();
}

void GraphWriter::writeGraph(Graph *graph, std::string outputPath)
{
    std::ofstream destinationFile;
    destinationFile.open(outputPath.c_str(), std::ios_base::out);

    this->visitedVertexes.clear();

    auto verticesIterator = graph->verticesIterator();

    while (!verticesIterator.end())
    {
        Vertex *vertex = *verticesIterator;

        auto neighborsIterator = vertex->neighborsIterator();

        while (!neighborsIterator.end())
        {
            Vertex *neighbor = *neighborsIterator;

            if (!vertexWasVisited(neighbor->getVertexId()))
            {
                destinationFile << vertex->getVertexId() << " " << neighbor->getVertexId()
                                << std::endl;
            }

            neighborsIterator++;
        }

        this->visitedVertexes.push_back(vertex->getVertexId());
        verticesIterator++;
    }

    destinationFile.close();
}

// FIXME This should not have to be a separate method. writeGraph should be able to write
// DirectedGraphs. Currently not able to convert/cast DirectedGraph to Graph (DONT KNOW WHY :()
void GraphWriter::writeDirectedGraph(DirectedGraph *graph, std::string outputPath)
{
    std::ofstream destinationFile;
    destinationFile.open(outputPath.c_str(), std::ios_base::out);

    this->visitedVertexes.clear();

    auto verticesIterator = graph->verticesIterator();

    while (!verticesIterator.end())
    {
        Vertex *vertex = *verticesIterator;

        auto neighborsIterator = vertex->neighborsIterator();

        while (!neighborsIterator.end())
        {
            Vertex *neighbor = *neighborsIterator;

            if (!vertexWasVisited(neighbor->getVertexId()))
            {
                destinationFile << vertex->getVertexId() << " " << neighbor->getVertexId()
                                << std::endl;
            }

            neighborsIterator++;
        }

        this->visitedVertexes.push_back(vertex->getVertexId());
        verticesIterator++;
    }

    destinationFile.close();
}

void GraphWriter::writeWeightedGraph(WeightedGraph *weightedGraph, std::string outputPath)
{
    std::ofstream destinationFile;
    destinationFile.open(outputPath.c_str(), std::ios_base::out);

    auto verticesIterator = weightedGraph->verticesIterator();

    while (!verticesIterator.end())
    {
        WeightedVertex *vertex = *verticesIterator;

        auto weightsIterator = vertex->weightsIterator();

        while (!weightsIterator.end())
        {
            if (!vertexWasVisited(weightsIterator->first))
            {
                destinationFile << vertex->getVertexId() << " " << weightsIterator->first << " "
                                << weightsIterator->second << std::endl;
            }

            weightsIterator++;
        }

        this->visitedVertexes.push_back(vertex->getVertexId());
        verticesIterator++;
    }

    destinationFile.close();
}
