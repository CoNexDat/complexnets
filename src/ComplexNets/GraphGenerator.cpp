#include "GraphGenerator.h"
#include "../ComplexNets/IGraphReader.h"
#include "../ComplexNets/GraphFactory.h"
#include "../ComplexNets/WeightedGraphFactory.h"
#include "../ComplexNets/ConexityVerifier.h"
#include "../ComplexNets/TraverserBFS.h"
#include <vector>
#include <math.h>

using namespace graphpp;

typedef struct Position { float x; float y; } Position;

vector<Position> vertexesPositions;
vector<unsigned int> vertexesFutureDegrees;

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
 * */

Graph* GraphGenerator::generateHotExtendedGraph(unsigned int m, unsigned int n, float xi,  unsigned int q, float r)
{
	Graph* graph = new Graph(false, false);
	vector<unsigned int> vertexIndexes;
	list<float> distance;

	vertexesPositions.clear();

	Vertex* newVertex = new Vertex(1);
	graph->addVertex(newVertex);	
	addVertexPosition();
	unsigned int root = 1;

	//VERTEX GENERATOR
	for(unsigned int i = 2; i <= n; i++)
	{
		newVertex = new Vertex(i);
		graph->addVertex(newVertex);
		addVertexPosition();

		float id[i];
		unsigned int count = 1;
		for(unsigned int j = 1; j <= i; j++)
		{
			unsigned int HopsDistance = graph->hops(graph->getVertexById(j), graph->getVertexById(root));
			float euclidianDistance = distanceBetweenVertex(j, i);
			float w = euclidianDistance + xi * HopsDistance;
			if(j != i)
			{
				distance.push_front(w);
				id[count++] = w;
			}
		}
		distance.sort();

		for (unsigned int k = 0; k < m; k++)
		{
			unsigned int t = 0;
			while(distance.front() != id[t] && !distance.empty())
				t++;
				
			if (t == 0)
				t++;
			Vertex* selectedVertex = graph->getVertexById(t);
			if(t != i && !selectedVertex->isNeighbourOf(newVertex))
			{
				vertexIndexes.push_back(t);
				vertexIndexes.push_back(i);
				graph->addVertex(newVertex);
				graph->addEdge(selectedVertex, newVertex);
				//cout<<id[t]<<" "<<distance.front()<<" "<<i<<" "<<t<<" "<<root<<"\n";
			}
			if (!distance.empty())
				distance.pop_front();
		}

		//EDGE GENERATOR
		count = 1;
		distance.clear();
		for(unsigned int j = 1; j <= i; j++)
		{
			float euclidianDistance = distanceBetweenVertex(j, root);
			unsigned int HopsWithEdge = 0;
			unsigned int HopsWithOutEdge = 0;
			for (unsigned int l = 1; l <= i; l++)
			{
				if (!graph->getVertexById(l)->isNeighbourOf(graph->getVertexById(root)))
				{
					HopsWithOutEdge = graph->hops(graph->getVertexById(l), graph->getVertexById(root))+HopsWithOutEdge;
					graph->addEdge(graph->getVertexById(l), graph->getVertexById(root));
					HopsWithEdge = graph->hops(graph->getVertexById(l), graph->getVertexById(root)) + HopsWithEdge;
					graph->removeEdge(graph->getVertexById(l), graph->getVertexById(root));
				}
			}
			float w = euclidianDistance + (r/i) * (HopsWithEdge - HopsWithOutEdge);
			if(w != 0)
			{
				distance.push_front(w);
				id[count++] = w;
			}
		}
		distance.sort();
		for (unsigned int k = 0; k < q; k++)
		{
			unsigned int t = 0;
			while(distance.front() != id[t] && !distance.empty())
				t++;

			if (t == 0)
				t++;
			if(t != i && !graph->getVertexById(t)->isNeighbourOf(graph->getVertexById(root)))
			{
				vertexIndexes.push_back(t);
				vertexIndexes.push_back(root);
				graph->addEdge(graph->getVertexById(t), graph->getVertexById(root));
				//cout<<distance.front()<<" "<<t<<" "<<i<<" "<<k<<" "<<root<<"\n";
			}
			if (!distance.empty())
				distance.pop_front();
		}
		distance.clear();
		root = vertexIndexes[rand() % vertexIndexes.size()];
	}
	vertexIndexes.clear();
	return graph;
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


/*
 EXPLICACION ALGORITMO

K VIENE COMO PARAMETRO CON UN HISTOGRAMA DE GRADOS, POR EJEMPLO EL VECTOR {9,7,5,4,3} SIGNIFICA QUE TIENE QUE HABER 9 NODOS CON GRADO 1, 7 NODOS CON GRADO 2, ETC

INICIALMENTE SE GENERAN TODOS LOS IDS DE LOS NODOS A AGREGAR Y SE PONEN EN EL VECTOR VEC, SUM TIENE LA CANTIDAD ACTUAL DE ELEMENTOS EN VEC

PARA QUE EL ALGORITMO FUNCIONE SEGUN SE HABLO CON IGNACIO, HAY QUE IR AGREGANDO LOS NODOS DE MAYOR GRADO Y LUEGO LOS DE MENOR GRADO. LAS VARIABLES actualDegree, actualDegreeAmount, actualDegreeStartIndex SE USAN PARA EN CADA ITERACION ELEGIR DE VEC UN NODO AL AZAR ENTRE LOS QUE HAY DE MAYOR GRADO POSIBLE.

PARA SIMPLIFICAR INICIALMENTE EL ALGORITMO Y NO CONTAR CON OTRA ESTRUCTURA DE DATOS, EL ID DEL VECTOR ESTA CONSTRUIDO DE MANERA QUE LA CIFRA DE MILES DEL ID REPRESENTA EL GRADO QUE SE DESEA QUE TENGA AL FINALIZAR EL ALGORITMO. LA FUNCION openDegrees, DADO UN NODO DEVUELVE LA CANTIDAD DE GRADOS LIBRES QUE TIENE COMPARANDO LOS VECINOS Y EL GRADO DESEADO QUE ESTA IMPLICITO EN SU ID.

PARA LA ETAPA 1 EL ALGORITMO ES:
1) SI ES EL PRIMER NODO, SE AGREGA AL GRAFO
2) SI NO ES EL PRIMER NODO, SE BUSCA AL AZAR UN NODO YA AGREGADO QUE TENGA GRADOS LIBRES, Y SE AGREGA EL NUEVO NODO AL GRADO CREANDO UNA ARISTA HACIA EL NODO BUSCADO. PARA PODER BUSCAR EFICIENTEMENTE UN NODO YA AGREGADO QUE TENGA GRADOS LIBRES, SE TIENE UN VECTOR vertexesWithFreeDegrees QUE SIEMPRE TIENE UN LISTADO DE LOS NODOS CON GRADOS LIBRES. EN ESTE VECTOR SE AGREGAN LOS NODOS QUE SE AGREGAN AL GRAFO CON GRADO >= 2 (YA QUE AL CONECTARSE A UN NODO LES QUEDA AL MENOS UN NODO LIBRE) Y CUANDO SE CREAN ARISTAS, SI EL NODO DESTINO ERA EL ULTIMO GRADO LIBRE QUE TENIA SE ELIMINA DEL VECTOR

PARA LA ETAPA 2 SE USA EL VECTOR vertexesWithFreeDegrees QUE DESPUES DE LA ETAPA 1 QUEDA CON TODOS LOS NODOS QUE TIENEN GRADOS LIBRES. SE RECORRER UNO POR UNO Y SE LO TRATA DE UNIR CON OTROS NODOS DEL VECTOR HASTA OCUPAR LOS GRADOS QUE TENIA LIBRES. SOLO SE PUEDE CONECTAR CON OTRO NODO SI NO ESTABAN CONECTADOS PREVIAMENTE Y SI EL NODO DESTINO TAMBIEN TIENE GRADOS LIBRES



*/

Graph* GraphGenerator::generateMolloyReedGraph(unsigned int k[])
{
	Graph* graph = new Graph(false, false);	
	unsigned int sum = 0, index, i, j, chosenId, existentVertexId, actualDegree, actualDegreeAmount = 0, actualDegreeStartIndex;
	vector<unsigned int> vec, vertexesWithFreeDegrees;
	Vertex* v;
	Vertex* existentVertex;
	Vertex* otherVertex;
	bool first=true;
	unsigned int kLength = 5;

	vertexesFutureDegrees.clear();
	
	// TODO: ACA EN VEZ DE 5 LITERAL HAY QUE OBTENER LA DIMENSION DEL ARRAY K
	for (i = 0; i < kLength; i++)
	{
		for (j = 1; j <= k[i]; j++){
			vec.push_back(++sum);
			vertexesFutureDegrees.push_back(i+1);
		}
	}

	actualDegree = kLength;
	actualDegreeStartIndex = sum;
	while (sum > 0)
	{
		if (actualDegreeAmount == 0) {
			actualDegreeAmount = k[--actualDegree];
			actualDegreeStartIndex = actualDegreeStartIndex - actualDegreeAmount;
		}

		cout << "sum vale: " << sum << "\n";
		cout << "Estoy extrayendo vertices de grado " << actualDegree << "\n";
		cout << "Quedan extraer " << actualDegreeAmount << "\n";

		// CON ESTA LINEA ELIJO UN INDICE DE VEC DE NODOS DEL GRADO QUE ESTOY ELIGIENDO
		index = actualDegreeStartIndex + (rand() % actualDegreeAmount);
		chosenId = vec[index];

		if (first)
		{
			// SI ES EL PRIMER NODO, UNICAMENTE LO AGREGO AL GRAFO Y A vertexesWithFreeDegrees
			// YA QUE SIEMPRE TIENE GRADOS LIBRES
			first = false;
			Vertex* newVertex = new Vertex(chosenId);
			graph->addVertex(newVertex);
			vertexesWithFreeDegrees.push_back(chosenId);
			cout << "Agrego vertice " << chosenId << "\n";
		}
		else
		{
			
			if (vertexesWithFreeDegrees.size()==0)
			{
				// ESTE CASO SE DARIA SI AL IR AGREGANDO NODOS SE GENERA UN GRAFO COMPLETO SIN GRADOS LIBRES
				// Y FALTAN AGREGAR MAS NODOS, HAY QUE CANCELAR EL ALGORITMO Y DEVUELVO EL GRAFO PARCIAL CREADO
				cout << "Error al generar el grafo\n";
				return graph;
			}
			else
			{
				// ELIJO AL AZAR UN NODO DE LOS EXISTENTES CON GRADOS LIBRES				
				existentVertexId = vertexesWithFreeDegrees[rand() % vertexesWithFreeDegrees.size()];
				existentVertex = graph->getVertexById(existentVertexId);
	
				Vertex* newVertex = new Vertex(chosenId);
				graph->addVertex(newVertex);
				graph->addEdge(existentVertex, newVertex);
				cout << "Agrego vertice " << chosenId << " unido a " << existentVertexId << "\n";
			
				// SI EL NUEVO NODO TIENE GRADOS LIBRES LO AGREGO AL VECTOR		
				if (openDegrees(newVertex) > 0)
					vertexesWithFreeDegrees.push_back(chosenId);

				// SI EL NODO VIEJO COMPLETO SU GRADO LO ELIMINO DEL VECTOR
				if (openDegrees(existentVertex)==0)
					for(i = 0; i < vertexesWithFreeDegrees.size(); i++)
						if(vertexesWithFreeDegrees[i] == existentVertexId)
							vertexesWithFreeDegrees.erase(vertexesWithFreeDegrees.begin() + i);
			}
		}
		// ELIMINO EL NODO DE LA LISTA DE NODOS A AGREGAR Y DECREMENTO CONTADORES
		vec.erase(vec.begin()+index);
		sum--;
		actualDegreeAmount--;

		// SI TERMINE DE AGREGAR LOS NODOS DEL GRADO ACTUAL, PASO AL GRADO SIGUIENTE
		if (actualDegreeAmount==0)
			cout << "Termine de poner los nodos de grado " << actualDegree << "\n";
	}
	cout << "Termine de generar todo el grafo!\n";
	// ACA TERMINA LA ETAPA 1 DEL ALGORITMO MOLLOY REED

	// DEBUG: IMPRIMO EL VECTOR CON NODOS LIBRES PREVIO A LA ETAPA 2 PARA VER SI FUNCIONA
	printVertexVector(graph,vertexesWithFreeDegrees);

	// NODO A NODO INTENTO LIBERAR LOS GRADOS LIBRES CONECTANDO CON OTROS NODOS DEL VECTOR
	for (i = 0; i < vertexesWithFreeDegrees.size(); i++)
	{
		v = graph->getVertexById(vertexesWithFreeDegrees[i]);
		cout << "QUIERO ENCONTRARLE VECINOS A " << vertexesWithFreeDegrees[i] << "\n";
		if (openDegrees(v) > 0)
		{
			// RECORRO TODOS LOS OTROS NODOS QUE TENGAN GRADOS LIBRES HASTA QUE NO ME QUEDEN MAS GRADOS LIBRES A MI
			for (j = i+1; j < vertexesWithFreeDegrees.size() && openDegrees(v) > 0; j++)
			{
				otherVertex = graph->getVertexById(vertexesWithFreeDegrees[j]);
				if (!v->isNeighbourOf(otherVertex) && openDegrees(otherVertex)>0)
				{
					cout << "Conecto el vertice " << vertexesWithFreeDegrees[i] << " con el vertice " << vertexesWithFreeDegrees[j] << "\n";
					graph->addEdge(v, otherVertex);
				}
			}
		}
	}
	// DEBUG: VUELVO A IMPRIMIR VECTOR CON NODOS LIBRES A VER SI FUNCIONO LA ETAPA2
	printVertexVector(graph,vertexesWithFreeDegrees);

	// TODO: ACA HAY QUE HACER LA ETAPA 3. DESPUES DE LA ETAPA 2 PUEDEN QUEDAR ALGUNOS CASOS DE NODOS QUE TENGAN GRADOS LIBRES Y QUE YA ESTEN CONECTADOS ENTRE SI. PARA SOLUCIONAR ESTO HAY QUE HACER UNA ESPECIE DE REWIRING, BUSCAR UN NODO, O UNA ARISTA Y HACER UN PUENTE A TRAVES DE ESTE PARA PODER CONECTAR LOS GRADOS LIBRES DE LOS NODOS RESTANTES.

	vertexesWithFreeDegrees.clear();
	vec.clear();
	return graph;
}

// DADO UN VECTOR DE IDS DE NODOS, LO RECORRE Y IMPRIME PARA CADA NODO EL ID, EL GRADO ACTUAL Y LOS GRADOS LIBRES.
void GraphGenerator::printVertexVector(Graph *graph, vector<unsigned int> vec)
{
	Vertex* v;
	for (unsigned int i=0;i<vec.size();i++)
	{
		v = graph->getVertexById(vec[i]);
		cout << "El vertice " << vec[i] << " tiene " << v->degree() << " vecinos, le faltan " << openDegrees(v) << "\n";
	}
}

// FUNCION QUE DADO UN VERTICE DEVUELVE LOS GRADOS LIBRES USANDO EL GRADO ESPERADO IMPLICITO EN EL ID
int GraphGenerator::openDegrees(Vertex* vertex)
{
	return vertexesFutureDegrees[vertex->getVertexId() - 1] - vertex->degree();
}
