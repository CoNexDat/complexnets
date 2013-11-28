// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

#include "GraphGenerator.h"
#include "../ComplexNets/IGraphReader.h"
#include "../ComplexNets/GraphFactory.h"
#include "../ComplexNets/WeightedGraphFactory.h"
#include "../ComplexNets/ConexityVerifier.h"
#include "../ComplexNets/TraverserBFS.h"
#include <vector>
#include <cmath>
#include <map>

using namespace graphpp;

typedef struct Position { float x; float y; } Position;


static const double PI = atan(1) * 4;

vector<Position> vertexesPositions;

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
	conexityVerifier.getBiggestComponent(graph);

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
 *
 * Algorithm summary
 * 1) Create the first vertex with random position and set it as root
 * 2) Create new vertexes V with random positions and then connect to the vertixes U which minimizes the euclidean distance from U to V and the hoops distance from U to root. This process is repeated m times for each new vertex added.
 * 3) Create q new edges on the graph for the vertex added
 * A new root is chosen with probability dependant on the node degree.
 * */

Graph* GraphGenerator::generateHotExtendedGraph(unsigned int m, unsigned int n, float xi,  unsigned int q, float r)
{
	Graph* graph = new Graph(false, false);
	vector<unsigned int> vertexIndexes;
	map<float,unsigned int> distance;

	vertexesPositions.clear();
	//Firts vertex
	Vertex* newVertex = new Vertex(1);
	graph->addVertex(newVertex);
	addVertexPosition();
	unsigned int root = 1;

	//Creation of vertex
	for(unsigned int i = 2; i <= n; i++)
	{
		newVertex = new Vertex(i);
		graph->addVertex(newVertex);
		addVertexPosition();
		for(unsigned int j = 1; j < i; j++) //this for evaluated "w" for each vertex in the graph
		{
			unsigned HopsDistance = graph->hops(graph->getVertexById(j), graph->getVertexById(root)); //distance between vertex evaluated and root vertex
			float euclidianDistance = distanceBetweenVertex(j, i); //Distance between vertex evaluated and new vertex
			float w = euclidianDistance + xi * HopsDistance;
				distance[w]=j; //stores 'w' as key of a map
		}
		addEdges(graph, newVertex,distance, m, &vertexIndexes);
		distance.clear();
		for(unsigned int j = 1; j <= i; j++) //selected the edges that will be added, is necessary to evaluate all nodes.
		{
			float euclidianDistance = 0;
			unsigned int HopsWithEdge = 0;
			unsigned int HopsWithOutEdge = 0;
			if (!graph->getVertexById(j)->isNeighbourOf(graph->getVertexById(root)) && j!=root) //If the node selected as candidate to add an edge is the root or is already connected, don't do anything
			{
				for (unsigned int l = 1; l <= i; l++) //Calculate the distance sumarize from each existant vertex to the root, with the edge and without it.
				{
					HopsWithOutEdge = graph->hops(graph->getVertexById(l), graph->getVertexById(root))+HopsWithOutEdge; //Hops between evaluated vertex and root vertex without new edge
					graph->addEdge(graph->getVertexById(j), graph->getVertexById(root)); //Add new edges only for evaluation, later will be removed
					HopsWithEdge = graph->hops(graph->getVertexById(l), graph->getVertexById(root)) + HopsWithEdge; //Hops between evaluated vertex and root vertex with new edge
					graph->removeEdge(graph->getVertexById(j), graph->getVertexById(root)); //remove the edge previously added
				}
				euclidianDistance = distanceBetweenVertex(j, root);
				float w = euclidianDistance + (r/i) * (HopsWithEdge - HopsWithOutEdge);
				distance[w]=j;
			}
		}
		addEdges(graph, graph->getVertexById(root),distance, q, &vertexIndexes);
		distance.clear();
		root = vertexIndexes[rand() % vertexIndexes.size()];
	}
	return graph;
}

void GraphGenerator::addEdges(Graph* graph, Vertex* vertex, map<float, unsigned int> distance, unsigned int quant, vector<unsigned int>* vertexIndexes)
{
	for (unsigned int k = 0; k < quant && !distance.empty(); k++) //Adding "q" new edges. The processes is similar to added vertex.
	{
		if(!graph->getVertexById(distance.begin()->second)->isNeighbourOf(vertex))
		{
			vertexIndexes->push_back(distance.begin()->second);
			vertexIndexes->push_back(vertex->getVertexId());
			graph->addEdge(graph->getVertexById(distance.begin()->second), vertex);
			distance.erase(distance.begin()); 			//Remove the lowest value of w from the list, because was used previously. This process repeat "q" times.
			if (distance.empty()) break;
		}
	}
}

float GraphGenerator::distanceBetweenVertex(unsigned int vertex1Id, unsigned int vertex2Id)
{
	
	return sqrt(pow(vertexesPositions[vertex1Id-1].x - vertexesPositions[vertex2Id-1].x, 2)
				 + pow(vertexesPositions[vertex1Id-1].y - vertexesPositions[vertex2Id-1].y, 2));
}


void GraphGenerator::addVertexPosition()
{
	vertexesPositions.push_back(Position());
	vertexesPositions.back().x = (float) rand() / RAND_MAX;
	vertexesPositions.back().y = (float) rand() / RAND_MAX;
}


Graph* GraphGenerator::generateMolloyReedGraph(string path)
{
	Graph *graph = new Graph(false, false);

    IGraphReader<Graph, Vertex> *reader = new MolloyReedGraphReader<Graph, Vertex>();
	reader->read(*graph, path);

	delete reader;

	return graph;
}

/*
 * Computes the distance in a hiperbolic space between two points
 */

inline double GraphGenerator::hiperbolicDistance(PolarPosition p1, PolarPosition p2) {
    return acosh(cosh(p1.r) * cosh(p2.r) - sinh(p1.r) * sinh(p2.r) * cos(fmod(abs(p1.theta - p2.theta), PI)));
}

/*
 * Computes random polar hyperbolic coordinates
 */
inline GraphGenerator::PolarPosition GraphGenerator::getRandomHyperbolicCoordinates(float a, double maxr) {
    PolarPosition pos;
    // generate theta in [0, 2pi]
    pos.theta = ((double)rand()/(double)RAND_MAX) * 2 * PI;
    // select a radius in (0, r)
    double u = ((double)rand()/(double)RAND_MAX);
    pos.r = acosh(u*(cosh(maxr*a) - 1) + 1) / a;
    return pos;
}

inline double GraphGenerator::getMaxRadius(int i, float a, float c) {
    return log((double)i / c) / a;
}

double GraphGenerator::getExpectedAvgNodeDeg(unsigned int i, float fa, float fc) {
    double a = (double) fa;
    double amh = a - 0.5;
    double c = (double) fc;
    double R = getMaxRadius(i, fa, fc);
    double c1 = 2 * pow(a, 3) / (PI * (pow(amh, 3)) * (pow(2 * a - 0.5, 3)));
    double c2 = (2 * a - PI * (amh)) / (2 * PI * amh);
    double c3 = a / (PI * pow(amh, 2));
    double c4 = (a / (PI * amh)) * (1 + a / (2 * pow(amh, 2)));
    return 2*a*c*(c1*exp(amh*R) - c2*a*pow(R,2) - R*c3 - c4);
}

/*
 * Papadopoulos Hiperbolic Graph Model
 * n is the total nodes number
 * a is the radial density of the graph.
 * c is the a parameter that determines the average degree of the graph.
 * */
Graph* GraphGenerator::generateHiperbolicGraph(unsigned int n, float a, float c)
{
	Graph* graph = new Graph(false, false);
	vector<PolarPosition> vPolarPos;
	PolarPosition sentinel;
	vPolarPos.push_back(sentinel);
	for (unsigned int i = 1; i <= n; i++) {
		Vertex* src = new Vertex(i);
		graph->addVertex(src);
		// compute the current disk radius
		double maxr = getMaxRadius(i, a, c);
		bool hasNeighbours = false;
		PolarPosition pos;
		do {
		    pos = getRandomHyperbolicCoordinates(a, maxr);
		    for (unsigned int j = 1; j < i; j++) {
			PolarPosition other = vPolarPos[j];
			if (hiperbolicDistance(pos, other) < maxr) {
			    hasNeighbours = true;
			    graph->addEdge(src, graph->getVertexById(j));
			}
		    }
		} while (!hasNeighbours && i != 1);
		vPolarPos.push_back(pos);
	}
	return graph;
	
}
