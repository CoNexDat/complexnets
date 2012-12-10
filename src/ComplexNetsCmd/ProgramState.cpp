#include "ProgramState.h"
#include "../ComplexNets/GraphGenerator.h"
#include "../ComplexNets/IBetweenness.h"
#include "../ComplexNets/IGraphFactory.h"
#include "../ComplexNets/GraphFactory.h"
#include "../ComplexNets/PropertyMap.h"
#include "../ComplexNets/DegreeDistribution.h"
#include "../ComplexNetsGui/inc/GrapherUtils.h"
#include "../ComplexNets/WeightedGraphFactory.h"
#include "../ComplexNets/DegreeDistribution.h"

using namespace std;
using namespace graphpp;
using namespace ComplexNetsGui;


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

void ProgramState::exportBetweennessVsDegree(string outputPath) {
    PropertyMap propertyMap;
    IGraphFactory<Graph, Vertex> *factory = new GraphFactory<Graph, Vertex>();
    IBetweenness<Graph, Vertex>* betweenness = factory->createBetweenness(this->graph);
    IBetweenness<Graph, Vertex>::BetweennessIterator betweennessIterator = betweenness->iterator();

    // Calculate betweenness.

    while (!betweennessIterator.end()) {
        propertyMap.addProperty<double>("betweenness", to_string<unsigned int>(betweennessIterator->first), betweennessIterator->second);
        ++betweennessIterator;
    }

    delete betweenness;

    // Calculate degree distribution.

    DegreeDistribution<Graph, Vertex>* degreeDistribution = factory->createDegreeDistribution(graph);
    DegreeDistribution<Graph, Vertex>::DistributionIterator degreeIterator = degreeDistribution->iterator();

    while (!degreeIterator.end()) {
        propertyMap.addProperty<double>("degreeDistribution", to_string<unsigned int>(degreeIterator->first), degreeIterator->second);
        propertyMap.addProperty<double>("degreeDistributionProbability", to_string<unsigned int>(degreeIterator->first), degreeIterator->second / (double)graph.verticesCount());
        ++degreeIterator;
    }

    delete degreeDistribution;

    double betweennessAuxAcum;
    unsigned int degreeAmount;
    VariantsSet betweennessVsDegree;
    VariantsSet& betweennessSet = propertyMap.getPropertySet("betweenness");
    VariantsSet& degreeDistributionSet = propertyMap.getPropertySet("degreeDistribution");
    VariantsSet::const_iterator it = degreeDistributionSet.begin();
    VariantsSet::const_iterator betwennessIt = betweennessSet.begin();
    VariantsSet::const_iterator betweennessVsDegreeIt;
    while (it != degreeDistributionSet.end())
    {
        betweennessVsDegree.insert<double>(it->first, 0.0);
        ++it;
    }

    while (betwennessIt != betweennessSet.end())
    {
        unsigned int vertedId = from_string<unsigned int>(betwennessIt->first);
        Vertex* v = graph.getVertexById(vertedId);
        betweennessAuxAcum = betweennessVsDegree.get_element<double>(to_string<unsigned int>(v->degree()));
        betweennessVsDegree.insert<double>(to_string<unsigned int>(v->degree()) , betweennessAuxAcum + from_string<unsigned int>(betwennessIt->second));

        ++betwennessIt;
    }

    betweennessVsDegreeIt = betweennessVsDegree.begin();
    while (betweennessVsDegreeIt != betweennessVsDegree.end())
    {
        std::string degree = betweennessVsDegreeIt->first;
        betweennessAuxAcum = from_string<double>(betweennessVsDegreeIt->second);
        degreeAmount = degreeDistributionSet.get_element<unsigned int>(degree);

        betweennessVsDegree.insert<double>(degree , betweennessAuxAcum / (double)degreeAmount);
        ++betweennessVsDegreeIt;
    }

    GrapherUtils utils;
    utils.exportPropertySet(betweennessVsDegree, outputPath);
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