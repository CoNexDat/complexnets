#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include "../ComplexNets/AdjacencyListGraph.h"
#include "../ComplexNets/WeightedVertexAspect.h"
#include "../ComplexNets/WeightedGraphAspect.h"

typedef graphpp::AdjacencyListVertex Vertex;
typedef graphpp::AdjacencyListGraph<Vertex> Graph;
typedef graphpp::WeightedVertexAspect<Vertex> WeightedVertex;
typedef graphpp::WeightedGraphAspect<WeightedVertex, graphpp::AdjacencyListGraph<WeightedVertex> > WeightedGraph;

#endif