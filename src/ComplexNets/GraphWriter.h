// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

#pragma once

#include "typedefs.h"

class GraphWriter
{
public:
    void writeGraph(Graph *graph, std::string outputPath);
    void writeWeightedGraph(WeightedGraph *WeightedGraph, std::string outputPath);
    void writeDirectedGraph(DirectedGraph *graph, std::string outputPath);

private:
    std::list<unsigned int> visitedVertexes;
    bool vertexWasVisited(unsigned int vertexId);
};
