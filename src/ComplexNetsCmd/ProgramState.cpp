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
#include "../ComplexNets/IShellIndex.h"
#include "../ComplexNets/IClusteringCoefficient.h"
#include "../ComplexNets/INearestNeighborsDegree.h"

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

void ProgramState::setExtendedHotGraph(unsigned int m, unsigned int n, float xi, unsigned int q, float r) {
    setWeighted(false);
    this->graph = *GraphGenerator::getInstance()->generateHotExtendedGraph(m, n, xi, q, r);
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

double ProgramState::clustering(unsigned int vertex_id) {
    double ret = -1;

    if (this->isWeighted())
            {
                WeightedVertex* vertex;
                if ((vertex = weightedGraph.getVertexById(vertex_id)) != NULL)
                {
                    IGraphFactory<WeightedGraph, WeightedVertex> *factory = new WeightedGraphFactory<WeightedGraph, WeightedVertex>();
                    IClusteringCoefficient<WeightedGraph, WeightedVertex>* clusteringCoefficient = factory->createClusteringCoefficient();
                    ret = clusteringCoefficient->vertexClusteringCoefficient(vertex);
                    delete clusteringCoefficient;
                }
            }
            else
            {
                Vertex* vertex;
                if ((vertex = graph.getVertexById(vertex_id)) != NULL)
                {
                    IGraphFactory<Graph, Vertex> *factory = new GraphFactory<Graph, Vertex>();
                    IClusteringCoefficient<Graph, Vertex>* clusteringCoefficient = factory->createClusteringCoefficient();
                    ret = clusteringCoefficient->vertexClusteringCoefficient(vertex);
                    delete clusteringCoefficient;
                }
            }

    return ret;
}

double ProgramState::knn(unsigned int vertex_id) {
    double ret = -1;
    if (this->isWeighted()) {
        WeightedVertex* vertex;
        if ((vertex = weightedGraph.getVertexById(vertex_id)) != NULL)
        {
            IGraphFactory<WeightedGraph, WeightedVertex> *factory = new WeightedGraphFactory<WeightedGraph, WeightedVertex>();
            INearestNeighborsDegree<WeightedGraph, WeightedVertex>* nearestNeighborsDegree = factory->createNearestNeighborsDegree();
            ret = nearestNeighborsDegree->meanDegreeForVertex(vertex);
            delete nearestNeighborsDegree;
        }
    }
    else
    {
        Vertex* vertex;
        if ((vertex = graph.getVertexById(vertex_id)) != NULL)
        {
            IGraphFactory<Graph, Vertex> *factory = new GraphFactory<Graph, Vertex>();
            INearestNeighborsDegree<Graph, Vertex>* nearestNeighborsDegree = factory->createNearestNeighborsDegree();
            ret = nearestNeighborsDegree->meanDegreeForVertex(vertex);
            delete nearestNeighborsDegree;
        }
    }
    return ret;
}

double ProgramState::shellIndex(unsigned int vertex_id) {
    double ret = -1;
    IGraphFactory<Graph, Vertex> *factory = new GraphFactory<Graph, Vertex>();
    IShellIndex<Graph, Vertex>* shellIndex = factory->createShellIndex(graph);
    IShellIndex<Graph, Vertex>::ShellIndexIterator it = shellIndex->iterator();
    while (!it.end())
    {
        if(it->first == vertex_id) {
            ret = it->second;
            break;
        }
        ++it;
    }
    delete shellIndex;
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
                break;
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
                break;
            }
            ++it;
        }
        delete degreeDistribution;
    }
    return ret;
}

void ProgramState::computeBetweenness(PropertyMap& propertyMap) {
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

        propertyMap.addProperty<double>("betweennessVsDegree", degree, betweennessAuxAcum / (double)degreeAmount);
        ++betweennessVsDegreeIt;
    }
}

void ProgramState::computeDegreeDistribution(PropertyMap& propertyMap) {
    if (isWeighted()) {
        IGraphFactory<WeightedGraph, WeightedVertex> *weightedFactory = new WeightedGraphFactory<WeightedGraph, WeightedVertex>();
        DegreeDistribution<WeightedGraph, WeightedVertex>* degreeDistribution = weightedFactory->createDegreeDistribution(this->weightedGraph);
        DegreeDistribution<WeightedGraph, WeightedVertex>::DistributionIterator it = degreeDistribution->iterator();

        while (!it.end()) {
            propertyMap.addProperty<double>("degreeDistribution", to_string<unsigned int>(it->first), it->second);
            propertyMap.addProperty<double>("degreeDistributionProbability", to_string<unsigned int>(it->first), it->second / (double) this->weightedGraph.verticesCount());
            ++it;
        }
        
        delete degreeDistribution;
    } else {
        IGraphFactory<Graph, Vertex> *factory = new GraphFactory<Graph, Vertex>();
        DegreeDistribution<Graph, Vertex>* degreeDistribution = factory->createDegreeDistribution(this->graph);
        DegreeDistribution<Graph, Vertex>::DistributionIterator it = degreeDistribution->iterator();
        
        while (!it.end()) {
            propertyMap.addProperty<double>("degreeDistribution", to_string<unsigned int>(it->first), it->second);
            propertyMap.addProperty<double>("degreeDistributionProbability", to_string<unsigned int>(it->first), it->second / (double) this->graph.verticesCount());
            ++it;
        }

        delete degreeDistribution;
    }
}

void ProgramState::computeClusteringCoefficient(PropertyMap& propertyMap) {
    if (!propertyMap.containsPropertySet("degreeDistribution")) {
        computeDegreeDistribution(propertyMap);
    }

    VariantsSet& degrees = propertyMap.getPropertySet("degreeDistribution");
    VariantsSet::const_iterator it = degrees.begin();

    double cc = 0;

    if (isWeighted()) {
        IGraphFactory<WeightedGraph, WeightedVertex> *weightedFactory = new WeightedGraphFactory<WeightedGraph, WeightedVertex>();
        IClusteringCoefficient<WeightedGraph, WeightedVertex> *clusteringCoefficient = weightedFactory->createClusteringCoefficient();
        while (it != degrees.end()) {
            cc = clusteringCoefficient->clusteringCoefficient(weightedGraph, from_string<unsigned int>(it->first));
            propertyMap.addProperty<double>("clusteringCoeficientForDegree", it->first, cc);
            ++it;
        }

        delete clusteringCoefficient;

    } else {
        IGraphFactory<Graph, Vertex> *factory = new GraphFactory<Graph, Vertex>();
        IClusteringCoefficient<Graph, Vertex>* clusteringCoefficient = factory->createClusteringCoefficient();
        while (it != degrees.end()) {
            cc = clusteringCoefficient->clusteringCoefficient(graph, from_string<unsigned int>(it->first));
            propertyMap.addProperty<double>("clusteringCoeficientForDegree", it->first, cc);
            ++it;
        }

        delete clusteringCoefficient;
    }
}

void ProgramState::computeNearestNeighborsDegree(PropertyMap& propertyMap) {
    if (!propertyMap.containsPropertySet("degreeDistribution")) {
        computeDegreeDistribution(propertyMap);
    }

    VariantsSet& degrees = propertyMap.getPropertySet("degreeDistribution");
    VariantsSet::const_iterator it = degrees.begin();

    double knn = 0;

    if (isWeighted()) {
        IGraphFactory<WeightedGraph, WeightedVertex> *weightedFactory = new WeightedGraphFactory<WeightedGraph, WeightedVertex>();
        INearestNeighborsDegree<WeightedGraph, WeightedVertex> *nearestNeighborDegree = weightedFactory->createNearestNeighborsDegree();

        while (it != degrees.end()) {
            knn = nearestNeighborDegree->meanDegree(weightedGraph, from_string<unsigned int>(it->first));
            propertyMap.addProperty<double>("nearestNeighborDegreeForDegree", it->first, knn);
            ++it;
        }

        delete nearestNeighborDegree;

    } else {
        IGraphFactory<Graph, Vertex> *factory = new GraphFactory<Graph, Vertex>();
        INearestNeighborsDegree<Graph, Vertex> *nearestNeighborDegree = factory->createNearestNeighborsDegree();

        while (it != degrees.end()) {
            knn = nearestNeighborDegree->meanDegree(graph, from_string<unsigned int>(it->first));
            propertyMap.addProperty<double>("nearestNeighborDegreeForDegree", it->first, knn);
            ++it;
        }

        delete nearestNeighborDegree;
    }
}

void ProgramState::exportBetweennessVsDegree(string outputPath) {
    PropertyMap propertyMap;
    computeBetweenness(propertyMap);
    GrapherUtils utils;
    utils.exportPropertySet(propertyMap.getPropertySet("betweennessVsDegree"), outputPath);
}

void ProgramState::exportDegreeDistribution(string outputPath) {
    PropertyMap propertyMap;
    computeDegreeDistribution(propertyMap);
    GrapherUtils grapherUtils;
    grapherUtils.exportPropertySet(propertyMap.getPropertySet("degreeDistribution"), outputPath);
}

void ProgramState::exportClusteringVsDegree(string outputPath) {
    PropertyMap propertyMap;
    computeClusteringCoefficient(propertyMap);
    GrapherUtils grapherUtils;
    grapherUtils.exportPropertySet(propertyMap.getPropertySet("clusteringCoeficientForDegree"), outputPath);
}

void ProgramState::exportNearestNeighborsDegreeVsDegree(string outputPath) {
    PropertyMap propertyMap;
    computeNearestNeighborsDegree(propertyMap);
    GrapherUtils grapherUtils;
    grapherUtils.exportPropertySet(propertyMap.getPropertySet("nearestNeighborDegreeForDegree"), outputPath);
}

void ProgramState::exportShellIndexVsDegree(string outputPath) {

}