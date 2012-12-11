#include "GraphGenerator.h"
#include "../ComplexNets/IGraphReader.h"
#include "../ComplexNets/GraphFactory.h"
#include "../ComplexNets/WeightedGraphFactory.h"
#include "../ComplexNets/ConexityVerifier.h"
#include "../ComplexNets/TraverserBFS.h"

using namespace graphpp;

GraphGenerator *GraphGenerator::instance = NULL;

GraphGenerator::GraphGenerator() {};

GraphGenerator *GraphGenerator::getInstance() {
	if (instance == NULL) {
		instance = new GraphGenerator();
	}

	return instance;
}


Graph *GraphGenerator::generateGraphFromFile(string path, bool directed, bool multigraph) {
	Graph *graph = new Graph(directed, multigraph);

   	IGraphFactory<Graph, Vertex> *factory = new GraphFactory<Graph, Vertex>();
    IGraphReader<Graph, Vertex> *reader = factory->createGraphReader();
	reader->read(*graph, path);

	delete reader;
	delete factory;

	return graph;
}


WeightedGraph *GraphGenerator::generateWeightedGraphFromFile(string path, bool directed, bool multigraph) {
	WeightedGraph *graph = new WeightedGraph(directed, multigraph);

   	IGraphFactory<WeightedGraph, WeightedVertex> *factory = new WeightedGraphFactory<WeightedGraph, WeightedVertex>();
    IGraphReader<WeightedGraph, WeightedVertex> *reader = factory->createGraphReader();
    reader->read(*graph, path);

	delete reader;
	delete factory;

	return graph;
}


Graph* GraphGenerator::generateErdosRenyiGraph(unsigned int n, float p)
{
	Graph* graph = new Graph(false, false);

	for (unsigned int i = 1; i <= n; i++) {
		graph->addVertex(new Vertex(i));
	}

	for (unsigned int i = 1; i < n; i++) {
		Vertex* srcVertex = graph->getVertexById(i);

		for (unsigned int j = i + 1; j <= n; j++) {
			Vertex* destVertex = graph->getVertexById(j);
			
			if ((float) rand() / RAND_MAX <= p)
				graph->addEdge(srcVertex, destVertex);
		}
	}

	// Keep only the biggest component (at least n/2 vertexes)
	ConexityVerifier<Graph, Vertex> conexityVerifier;
	conexityVerifier.getBigestComponent(graph);

	return graph;
}

Graph* GraphGenerator::generateBarabasiAlbertGraph(unsigned int m_0, unsigned int m, unsigned int n)
{
	Graph* graph = new Graph(false, false);
	// Create a K_M_0 graph				
	for(unsigned int i = 1; i <= m_0; i++)
		graph->addVertex(new Vertex(i));
	for(unsigned int i = 1; i < m_0; i++) 
	{
		Vertex* srcVertex = graph->getVertexById(i);
		for(unsigned int j = i+1; j <= m_0; j++)
		{
			Vertex* destVertex = graph->getVertexById(j);
			graph->addEdge(srcVertex, destVertex);
		}
	}

	// Fill the array with k apparitions of each vertex where k is the degree of the vertex
	vector<unsigned int> vertexIndexes;
	for(unsigned int i = 1; i <= m_0; i++)
		for(unsigned int k = 0; k < m_0; k++)
			vertexIndexes.push_back(i);

	for(unsigned int i = m_0+1; i <= n; i++)
	{
		unsigned int k = 0;
		Vertex* newVertex = new Vertex(i);
		while(k < m)
		{
			unsigned int index = vertexIndexes[rand() % vertexIndexes.size()];
			Vertex* selectedVertex = graph->getVertexById(index);
			// It isn't the same vertex and it isn't connected
			if(index != i && !selectedVertex->isNeighbourOf(newVertex))
			{
				vertexIndexes.push_back(index);
				vertexIndexes.push_back(i);
				graph->addVertex(newVertex);
				graph->addEdge(selectedVertex, newVertex);		
				k++;
			}
		}
	}
	vertexIndexes.clear();
	return graph;
}
/*
 * HOT Extended Model
 * m represents the number of edges in each new vertex
 * n is the total nodes number
 * xi is the parameter used to select the neighbors for new vertex.
 * q  represents the number of edges added in the graph after of connect a vertex.
 * r is the parameter user to selected the edges in the graph after of connect a vertex.
 * */

Graph* GraphGenerator::generateHotExtendedGraph(unsigned int m, unsigned int n, float xi,  unsigned int q, float r)
{
	Graph* graph = new Graph(false, false);
	vector<unsigned int> vertexIndexes;
	ConexityVerifier<Graph, Vertex> conexityVerifier;
	graph->addVertex(new Vertex(1));
	Vertex* newVertex1 = graph->getVertexById(1);
	newVertex1->setPosition((float) rand() / RAND_MAX,(float) rand() / RAND_MAX);
	unsigned int root =1;

//VERTEX GENERATOR
	for(unsigned int i = 2; i <= n; i++)
	{
		graph->addVertex(new Vertex(i));
		Vertex* newVertex = graph->getVertexById(i);
		newVertex->setPosition((float) rand() / RAND_MAX,(float) rand() / RAND_MAX);
		list<float> distance;
		float id[i];
		distance.clear();
		unsigned int count=1;
		for(unsigned int j=1; j<=i;j++)
		{
			unsigned int HopsDistance=conexityVerifier.hopsBetweenVertex(graph->getVertexById(j),graph->getVertexById(root));
			float euclidianDistance=conexityVerifier.distanceBetweenVertex(graph->getVertexById(j),graph->getVertexById(i));
			float w=euclidianDistance+xi*HopsDistance;
			if(j!=i)
			{
				distance.push_front(w);
				id[count]=w;
				count++;
			}
		}
		distance.sort();

		for (unsigned int k = 0; k<m;k++)
		{
			unsigned int t=0;
			while(distance.front()!=id[t] && !distance.empty())
				{
				t++;
				}
			if (t==0)t++;
			Vertex* selectedVertex = graph->getVertexById(t);
			if(t != i && !selectedVertex->isNeighbourOf(newVertex))
			{
				vertexIndexes.push_back(t);
				vertexIndexes.push_back(i);
				graph->addVertex(newVertex);
				graph->addEdge(selectedVertex, newVertex);
				//cout<<id[t]<<" "<<distance.front()<<" "<<i<<" "<<t<<" "<<root<<"\n";
			}
			if (!distance.empty())distance.pop_front();
		}
//EDGE GENERATOR
		count=1;
		distance.clear();
		for(unsigned int j=1; j<=i;j++)
		{
			float	euclidianDistance=conexityVerifier.distanceBetweenVertex(graph->getVertexById(j),graph->getVertexById(root));
			unsigned int 	HopsWithEdge=0;
			unsigned int	HopsWithOutEdge=0;
			for (unsigned int l=1; l<=i;l++)
			{
				if (!graph->getVertexById(l)->isNeighbourOf(graph->getVertexById(root)))
				{
				HopsWithOutEdge=conexityVerifier.hopsBetweenVertex(graph->getVertexById(l),graph->getVertexById(root))+HopsWithOutEdge;
				graph->addEdge(graph->getVertexById(l), graph->getVertexById(root));
				HopsWithEdge=conexityVerifier.hopsBetweenVertex(graph->getVertexById(l),graph->getVertexById(root))+HopsWithEdge;
				graph->removeEdge(graph->getVertexById(l), graph->getVertexById(root));
				}
			}
			float w=euclidianDistance+(r/i)*(HopsWithEdge-HopsWithOutEdge);
			if(w!=0)
			{
				distance.push_front(w);
				id[count]=w;
				count++;
			}

		}
		distance.sort();
		for (unsigned int k = 0; k<q;k++)
			{
				unsigned int t=0;
				while(distance.front()!=id[t] && !distance.empty())
				{
					t++;
				}
				if (t==0)t++;
				if(t != i && !graph->getVertexById(t)->isNeighbourOf(graph->getVertexById(root)))
				{
					vertexIndexes.push_back(t);
					vertexIndexes.push_back(root);
					graph->addEdge(graph->getVertexById(t), graph->getVertexById(root));
					//cout<<distance.front()<<" "<<t<<" "<<i<<" "<<k<<" "<<root<<"\n";
				}
				if (!distance.empty())distance.pop_front();
			}
		root= vertexIndexes[rand() % vertexIndexes.size()];
	}
	return graph;
}
