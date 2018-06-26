// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

#pragma once

#include "MolloyReedGraphReader.h"
#include "typedefs.h"

class GraphGenerator
{
private:
    typedef struct PolarPosition
    {
        double r;
        double theta;
    } PolarPosition;

    GraphGenerator();

    static GraphGenerator* instance;
    float distanceBetweenVertex(unsigned int vertex1Id, unsigned int vertex2Id);
    void addVertexPosition();
    void addEdges(
        Graph* graph,
        Vertex* vertex,
        std::map<float, unsigned int> distance,
        unsigned int quant,
        std::vector<unsigned int>* vertexIndexes);
    inline double hiperbolicDistance(PolarPosition p1, PolarPosition p2);
    inline double getMaxRadius(int i, float a, float c);
    inline PolarPosition getRandomHyperbolicCoordinates(float a, double maxr);

public:
    static GraphGenerator* getInstance();
    void addOriginalVertex(Graph* graph);
    void addFKPNode(
        unsigned int vertexIndex,
        Graph* graph,
        unsigned int root,
        float xi,
        std::vector<unsigned int>* vertexIndexes,
        unsigned int m);
    void addExtendedEdges(
        unsigned int q,
        unsigned int vertexIndex,
        Graph* graph,
        unsigned int root,
        float r,
        std::vector<unsigned int>* vertexIndexes);
    int chooseNewRoot(
        unsigned int vertexIndex,
        unsigned int t,
        unsigned int root,
        std::vector<unsigned int> vertexIndexes);

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
