#ifndef MOLLOYREEDGRAPHREADER_H
#define MOLLOYREEDGRAPHREADER_H

#include <string>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <math.h>
#include "IGraphReader.h"

namespace graphpp
{

using namespace std;

template <class Graph, class Vertex>
class MolloyReedGraphReader : public  IGraphReader<Graph, Vertex>
{
public:

	vector<unsigned int> vertexesFutureDegrees;

    typedef string FileName;
    typedef unsigned int LineNumber;

    virtual void read(Graph& graph, string source)
    {
		map<unsigned int, unsigned int> k;
		unsigned int degree, amount;
		ifstream sourceFile;
        sourceFile.open(source.c_str(), ios_base::in);

        if (!sourceFile)
            throw FileNotFoundException(source);

		string line;
        currentLineNumber = 1;
        while (getline(sourceFile, line))
        {
            string tree_str = line;
            character = tree_str.c_str();
            if (!isEmptyLine())
            {
				degree = readUnsignedInt();
                consume_whitespace();
				amount = readUnsignedInt();
				k[degree] = amount;
				consume_whitespace();
            }
            ++currentLineNumber;
        }

        sourceFile.close();

		molloyReedAlgorithm(graph, k);		
    }

    LineNumber getLineNumber() const
    {
        return currentLineNumber;
    }

private:

	void molloyReedAlgorithm(Graph& graph, map<unsigned int, unsigned int> k) {

		unsigned int sum = 0, index, i, j, chosenId, existentVertexId, actualDegree, actualDegreeAmount = 0, actualDegreeStartIndex;
		vector<unsigned int> vec, vertexesWithFreeDegrees;
		Vertex* v;
		Vertex* existentVertex;
		Vertex* otherVertex;
		map<unsigned int, unsigned int>::iterator it;
		map<unsigned int, unsigned int>::reverse_iterator rit;
		bool first=true;

		vertexesFutureDegrees.clear();

		for (it = k.begin(); it != k.end(); it++)
		{			
			for (i = 0; i < it->second; i++){
				vec.push_back(++sum);
				vertexesFutureDegrees.push_back(it->first);
			}
		}
		
		rit = k.rbegin();
		actualDegreeStartIndex = sum;
		while (sum > 0)
		{
			if (actualDegreeAmount == 0) {
				actualDegree = rit->first;
				actualDegreeAmount = rit->second;
				actualDegreeStartIndex = actualDegreeStartIndex - actualDegreeAmount;
				if(rit != k.rend())
					rit++;
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
				graph.addVertex(newVertex);
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
					return;
				}
				else
				{
					// ELIJO AL AZAR UN NODO DE LOS EXISTENTES CON GRADOS LIBRES				
					existentVertexId = vertexesWithFreeDegrees[rand() % vertexesWithFreeDegrees.size()];
					existentVertex = graph.getVertexById(existentVertexId);
	
					Vertex* newVertex = new Vertex(chosenId);
					graph.addVertex(newVertex);
					graph.addEdge(existentVertex, newVertex);
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
		printVertexVector(graph, vertexesWithFreeDegrees);

		// NODO A NODO INTENTO LIBERAR LOS GRADOS LIBRES CONECTANDO CON OTROS NODOS DEL VECTOR
		for (i = 0; i < vertexesWithFreeDegrees.size(); i++)
		{
			v = graph.getVertexById(vertexesWithFreeDegrees[i]);
			cout << "QUIERO ENCONTRARLE VECINOS A " << vertexesWithFreeDegrees[i] << "\n";
			if (openDegrees(v) > 0)
			{
				// RECORRO TODOS LOS OTROS NODOS QUE TENGAN GRADOS LIBRES HASTA QUE NO ME QUEDEN MAS GRADOS LIBRES A MI
				for (j = i+1; j < vertexesWithFreeDegrees.size() && openDegrees(v) > 0; j++)
				{
					otherVertex = graph.getVertexById(vertexesWithFreeDegrees[j]);
					if (!v->isNeighbourOf(otherVertex) && openDegrees(otherVertex)>0)
					{
						cout << "Conecto el vertice " << vertexesWithFreeDegrees[i] << " con el vertice " << vertexesWithFreeDegrees[j] << "\n";
						graph.addEdge(v, otherVertex);
					}
				}
			}
		}
		// DEBUG: VUELVO A IMPRIMIR VECTOR CON NODOS LIBRES A VER SI FUNCIONO LA ETAPA2
		printVertexVector(graph, vertexesWithFreeDegrees);

		// TODO: ACA HAY QUE HACER LA ETAPA 3. DESPUES DE LA ETAPA 2 PUEDEN QUEDAR ALGUNOS CASOS DE NODOS QUE TENGAN GRADOS LIBRES Y QUE YA ESTEN CONECTADOS ENTRE SI. PARA SOLUCIONAR ESTO HAY QUE HACER UNA ESPECIE DE REWIRING, BUSCAR UN NODO, O UNA ARISTA Y HACER UN PUENTE A TRAVES DE ESTE PARA PODER CONECTAR LOS GRADOS LIBRES DE LOS NODOS RESTANTES.

		vertexesWithFreeDegrees.clear();
		vec.clear();
	}


	// DADO UN VECTOR DE IDS DE NODOS, LO RECORRE Y IMPRIME PARA CADA NODO EL ID, EL GRADO ACTUAL Y LOS GRADOS LIBRES.
	void printVertexVector(Graph& graph, vector<unsigned int> vec)
	{
		Vertex* v;
		for (unsigned int i=0;i<vec.size();i++)
		{
			v = graph.getVertexById(vec[i]);
			cout << "El vertice " << vec[i] << " tiene " << v->degree() << " vecinos, le faltan " << openDegrees(v) << "\n";
		}
	}

	int openDegrees(Vertex* vertex)
	{
		return vertexesFutureDegrees[vertex->getVertexId() - 1] - vertex->degree();
	}

    std::string getLineNumberText() const
    {
        std:: stringstream s;
        s << "Line: " << currentLineNumber;
        return s.str();
    }

    unsigned int readUnsignedInt()
    {
        unsigned int ret = 0;
        if (!in_range(*character, '0', '9'))
            throw UnsignedIntegerMalformedException(getLineNumberText());
        else
        {
            std::string branchLenStr;
            while (in_range(*character, '0', '9'))
            {
                branchLenStr += *character;
                ++character;
            }

            if (!from_string<unsigned int>(branchLenStr, ret))
                throw UnsignedIntegerMalformedException(getLineNumberText());
        }
        return ret;
    }

    bool isEmptyLine()
    {
        bool ret = false;
        consume_whitespace();
        if (*character == '\0')
            ret = true;
        return ret;
    }

    void consume_whitespace()
    {
        while (*character == ' ' || *character == '\t')
            ++character;
    }


    LineNumber currentLineNumber;
    const char* character;
};
}

#endif

