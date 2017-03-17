// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

#ifndef PROGRAM_STATE_H
#define PROGRAM_STATE_H

#include "ComplexNets/PropertyMap.h"
#include "ComplexNets/typedefs.h"

#include "ComplexNets/AdjacencyListGraph.h"
#include "ComplexNets/AdjacencyListVertex.h"
#include "ComplexNets/IGraphFactory.h"

using namespace graphpp;

class ProgramState
{
private:
    bool weighted;
    bool digraph;
    WeightedGraph weightedGraph;
    DirectedGraph directedGraph;
    Graph graph;
    bool directed_out;
    bool directed_in;

    void computeBetweenness(PropertyMap& propertyMap);
    void computeDegreeDistribution(PropertyMap& propertyMap);
    void computeClusteringCoefficient(PropertyMap& propertyMap);
    void computeNearestNeighborsDegree(PropertyMap& propertyMap);
    void computeShellIndex(PropertyMap& propertyMap);

    bool computeMaxCliqueDistr(PropertyMap& propertyMap, bool exact, unsigned int max_time);

    std::string getDirectedPostfix();

public:
    ProgramState();

    void setWeighted(bool weighted);
    void setDigraph(bool digraph);

    bool isWeighted();
    bool isDigraph();
    WeightedGraph getWeightedGraph();
    DirectedGraph getDirectedGraph();
    Graph getGraph();

    void readGraphFromFile(std::string path);
    void setErdosRenyiGraph(unsigned int n, float p);
    void setBarabasiAlbertGraph(unsigned int m_0, unsigned int m, unsigned int n);
    void setExtendedHotGraph(
        unsigned int m, unsigned int n, float xi, unsigned int q, float r, unsigned int t);
    void setMolloyReedGraph(std::string path);
    void setHiperbolicGraph(unsigned int n, float a, float c);

    double betweenness(unsigned int vertex_id);
    double wbetweenness(unsigned int vertex_id);

    double degreeDistribution(unsigned int vertex_id);
    double clustering(unsigned int vertex_id);
    double knn(unsigned int vertex_id);
    double shellIndex(unsigned int vertex_id);
    std::list<int> maxCliqueExact(unsigned int max_time);
    std::list<int> maxCliqueAprox();

    double inDegreeDistribution(unsigned int vertex_id);
    double outDegreeDistribution(unsigned int vertex_id);

    void printDegrees();

    bool exportMaxCliqueExact(std::string outputPath, unsigned int max_time);
    void exportMaxCliqueAprox(std::string outputPath);
    void exportCurrentGraph(std::string outputPath);
    void exportBetweennessVsDegree(std::string outputPath);
    void exportDegreeDistribution(std::string outputPath,
                                  unsigned int log_bin_given = false,
                                  unsigned int binsAmount = -1);
    void exportClusteringVsDegree(std::string outputPath);
    void exportNearestNeighborsDegreeVsDegree(std::string outputPath);
    void exportShellIndexVsDegree(std::string outputPath);
    void exportCCBoxplot(std::string outputPath);

    void setDirectedInOut(bool o, bool i);

    graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry
    computeTotalBpEntriesDegreeDistribution();

    graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry computeTotalBpEntriesShellIndex();

    graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry computeTotalBpEntriesBetweenness();

    graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry computeTotalBpEntriesKnn();

    graphpp::IClusteringCoefficient<Graph, Vertex>::Boxplotentry computeTotalBpEntries();
};

#endif
