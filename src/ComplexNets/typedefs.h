// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include "ComplexNets/AdjacencyListGraph.h"
#include "ComplexNets/WeightedVertexAspect.h"
#include "ComplexNets/WeightedGraphAspect.h"
#include "ComplexNets/DirectedGraphAspect.h"
#include "ComplexNets/DirectedVertexAspect.h"

typedef graphpp::AdjacencyListVertex Vertex;
typedef graphpp::AdjacencyListGraph<Vertex> Graph;
typedef graphpp::WeightedVertexAspect<Vertex> WeightedVertex;
typedef graphpp::WeightedGraphAspect<WeightedVertex, graphpp::AdjacencyListGraph<WeightedVertex> > WeightedGraph;
typedef graphpp::DirectedVertexAspect<Vertex> DirectedVertex;
typedef graphpp::DirectedGraphAspect<DirectedVertex, graphpp::AdjacencyListGraph<DirectedVertex> > DirectedGraph;
#endif
