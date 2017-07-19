// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

#pragma once

#include "ComplexNets/MolloyReedGraphReader.h"
#include "ComplexNets/NearestNeighbor.h"
#include "ComplexNets/Position.h"
#include "ComplexNets/typedefs.h"

class GraphGenerator
{
private:
    GraphGenerator();

    static GraphGenerator* instance;

    // members related to hyperbolic graphs
    double hiperbolicDistance(PolarPosition p1, PolarPosition p2);
    double getMaxRadius(int i, float a, float c);
    PolarPosition getRandomHyperbolicCoordinates(float a, double maxr);

    // members related to HOT Extended graphs
    void addPosition(Vertex* v);
    NearestNeighbor* singleHopNN(unsigned hop);
    NearestNeighbor* doubleHopNN(unsigned hop1, unsigned hop2);

    void insertNN(NearestNeighbor* nn, Vertex *v);
    void removeNN(NearestNeighbor* nn, Vertex *v);
    Vertex* getNN(Graph* g, NearestNeighbor* nn, Vertex *v);

    double distance(Vertex* v1, Vertex* v2);
    double weightChange(Vertex* v);
    unsigned childCount(Vertex* v);
    Position position(Vertex* v);

public:
    static GraphGenerator* getInstance();

    Graph* generateGraphFromFile(std::string path, bool directed, bool multigraph);
    DirectedGraph* generateDirectedGraphFromFile(std::string path, bool multigraph);
    WeightedGraph* generateWeightedGraphFromFile(std::string path, bool directed, bool multigraph);
    Graph* generateErdosRenyiGraph(unsigned int n, float p);
    Graph* generateBarabasiAlbertGraph(unsigned int m_0, unsigned int m, unsigned int n);
    Graph* generateHotExtendedGraph(
        unsigned int m, unsigned int n, float xi, unsigned int q, float r, unsigned int t);
    Graph* generateMolloyReedGraph(std::string path);
    Graph* generateHiperbolicGraph(unsigned int n, float a, float c);
    double getExpectedAvgNodeDeg(unsigned int n, float a, float c);
};
