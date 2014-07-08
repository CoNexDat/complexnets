// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

#ifndef PROGRAM_STATE_H
#define PROGRAM_STATE_H

#include "../ComplexNets/typedefs.h"
#include "../ComplexNets/PropertyMap.h"

using namespace std;
using namespace graphpp;

class ProgramState {

private:
	bool weighted;
	bool digraph;
    WeightedGraph weightedGraph;
	DirectedGraph directedGraph;
    Graph graph;

    void computeBetweenness(PropertyMap& propertyMap);
    void computeDegreeDistribution(PropertyMap& propertyMap);
    void computeClusteringCoefficient(PropertyMap& propertyMap);
    void computeNearestNeighborsDegree(PropertyMap& propertyMap);
    void computeShellIndex(PropertyMap &propertyMap);

	bool computeMaxCliqueDistr(PropertyMap &propertyMap,bool exact, unsigned int max_time);
public:
	ProgramState();

	void setWeighted(bool weighted);
	void setDigraph(bool digraph);
	
	bool isWeighted();
	bool isDigraph();
	WeightedGraph getWeightedGraph();
	DirectedGraph getDirectedGraph();
	Graph getGraph();

	void readGraphFromFile(string path);
	void setErdosRenyiGraph(unsigned int n, float p);
	void setBarabasiAlbertGraph(unsigned int m_0, unsigned int m, unsigned int n);
	void setExtendedHotGraph(unsigned int m, unsigned int n, float xi, unsigned int q, float r);
	void setMolloyReedGraph(string path);
	void setHiperbolicGraph(unsigned int n, float a, float c);

	double betweenness(unsigned int vertex_id);
	double degreeDistribution(unsigned int vertex_id);
	double clustering(unsigned int vertex_id);
	double knn(unsigned int vertex_id);
	double shellIndex(unsigned int vertex_id);
	double maxCliqueExact(unsigned int max_time);
	double maxCliqueAprox();

	double inDegreeDistribution(unsigned int vertex_id);
	double outDegreeDistribution(unsigned int vertex_id);
	
	void printDegrees();
	
	bool exportMaxCliqueExact(string outputPath, unsigned int max_time);
	void exportMaxCliqueAprox(string outputPath);
	void exportCurrentGraph(string outputPath);
	void exportBetweennessVsDegree(string outputPath);
	void exportDegreeDistribution(string outputPath, unsigned int log_bin_given = false, unsigned int binsAmount = -1);
	void exportClusteringVsDegree(string outputPath);
	void exportNearestNeighborsDegreeVsDegree(string outputPath);
	void exportShellIndexVsDegree(string outputPath);
};

#endif
