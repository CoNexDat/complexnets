#ifndef PROGRAM_STATE_H
#define PROGRAM_STATE_H

#include "../ComplexNets/typedefs.h"
#include "../ComplexNets/PropertyMap.h"

using namespace std;
using namespace graphpp;

class ProgramState {

private:
	bool weighted;
    WeightedGraph weightedGraph;
    Graph graph;

    void computeBetweenness(PropertyMap& propertyMap);
    void computeDegreeDistribution(PropertyMap& propertyMap);
    void computeClusteringCoefficient(PropertyMap& propertyMap);
    void computeNearestNeighborsDegree(PropertyMap& propertyMap);
    void computeShellIndex(PropertyMap &propertyMap);

public:
	void setWeighted(bool weighted);

	bool isWeighted();
	WeightedGraph getWeightedGraph();
	Graph getGraph();

	void readGraphFromFile(string path);
	void setErdosRenyiGraph(unsigned int n, float p);
	void setBarabasiAlbertGraph(unsigned int m_0, unsigned int m, unsigned int n);
	void setExtendedHotGraph(unsigned int m, unsigned int n, float xi, unsigned int q, float r);

	double betweenness(unsigned int vertex_id);
	double degreeDistribution(unsigned int vertex_id);
	double clustering(unsigned int vertex_id);
	double knn(unsigned int vertex_id);
	double shellIndex(unsigned int vertex_id);

	void exportBetweennessVsDegree(string outputPath);
	void exportDegreeDistribution(string outputPath);
	void exportClusteringVsDegree(string outputPath);
	void exportNearestNeighborsDegreeVsDegree(string outputPath);
	void exportShellIndexVsDegree(string outputPath);
};

#endif