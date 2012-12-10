#include "ProgramState.h"
#include "../ComplexNets/GraphGenerator.h"
#include "../ComplexNets/IBetweenness.h"
#include "../ComplexNets/IGraphFactory.h"
#include "../ComplexNets/GraphFactory.h"
#include "../ComplexNets/WeightedGraphFactory.h"
#include "../ComplexNets/DegreeDistribution.h"


using namespace std;
using namespace graphpp;


void ProgramState::setWeighted(bool weighted) {
    this->weighted = weighted;
}

bool ProgramState::isWeighted() {
	return this->weighted;
}

WeightedGraph ProgramState::getWeightedGraph() {
	return this->weightedGraph;
}

Graph ProgramState::getGraph() {
	return this->graph;
}

void ProgramState::readGraphFromFile(string path) {
	if (isWeighted()) {
		this->weightedGraph = *(GraphGenerator::getInstance()->generateWeightedGraphFromFile(path, false, false));
    } else {
    	this->graph = *(GraphGenerator::getInstance()->generateGraphFromFile(path, false, false));
    }
}

void ProgramState::setErdosRenyiGraph(unsigned int n, float p) {
	setWeighted(false);
	this->graph = *GraphGenerator::getInstance()->generateErdosRenyiGraph(n, p);
}

void ProgramState::setBarabasiAlbertGraph(unsigned int m_0, unsigned int m, unsigned int n) {
	setWeighted(false);
	this->graph = *GraphGenerator::getInstance()->generateBarabasiAlbertGraph(m_0, m, n);
}

double ProgramState::betweenness(unsigned int vertex_id) {
	IGraphFactory<Graph, Vertex> *factory = new GraphFactory<Graph, Vertex>();
	IBetweenness<Graph, Vertex>* betweenness = factory->createBetweenness(this->graph);
    IBetweenness<Graph, Vertex>::BetweennessIterator it = betweenness->iterator();
    double ret = -1;
    while (!it.end())
    {
     	if(it->first == vertex_id) {
     		ret = it->second;
     		break;
     	}
        ++it;
    }
    delete betweenness;
    return ret;
}

double ProgramState::degreeDistribution(unsigned int vertex_id) {
	double ret = -1;
	if (this->isWeighted()){
		IGraphFactory<WeightedGraph, WeightedVertex> *factory = new WeightedGraphFactory<WeightedGraph, WeightedVertex>();
        DegreeDistribution<WeightedGraph, WeightedVertex>* degreeDistribution = factory->createDegreeDistribution(this->weightedGraph);
        DegreeDistribution<WeightedGraph, WeightedVertex>::DistributionIterator it = degreeDistribution->iterator();
        while (!it.end())
        {
           if(it->first == vertex_id) {
        		ret = it->second;
        	}
            ++it;
        }
        delete degreeDistribution;
	} else {
		IGraphFactory<Graph, Vertex> *factory = new GraphFactory<Graph, Vertex>();
        DegreeDistribution<Graph, Vertex>* degreeDistribution = factory->createDegreeDistribution(this->graph);
        DegreeDistribution<Graph, Vertex>::DistributionIterator it = degreeDistribution->iterator();
        while (!it.end())
        {
        	if(it->first == vertex_id) {
        		ret = it->second;
        	}
            ++it;
        }
        delete degreeDistribution;
    }
    return ret;
}