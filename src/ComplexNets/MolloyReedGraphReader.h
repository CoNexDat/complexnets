// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

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
    typedef typename Vertex::VerticesIterator NeighborsIterator;

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

	/*
	Algorithm summary

	k is an histogram with the degree distribution

	Iniallty all the future nodes are created with their ids and stored in "vec" vector

	We have to choose randomly nodes from vec. It's necessary for the algorithm to choose first the nodes with greater degree first. If not the graph could be complete before finishing the process of adding nodes
	In order to choose randomnly nodes from one degree, we use the variables actualDegree, actualDegreeAmount, actualDegreeStartIndex
	In other map we store the future degree that each vertex needs to have after the algoritmh finishes.
	
	First Step:
	The first node is added simply added to the graph
	Secuentially the nodes are added to the graph and connected with an existant vertex that has free degrees. 
	There is a vector vertexesWithFreeDegrees that stores de vertexes that had free degrees. Each time a node is added, an existant node is randomly selected from this vector.
	Free degree of a vertex is calculated from the differente between its future degree stored and the neighbours count (actual degree)
	
	Second step:
	After first step, could be some nodes with free degrees, they will be listed on vertexesWithFreeDegrees. Randomly we get two nodes from this vector that are not connected and connect them.
	If after adding the edge, one of them is full-degree, it's removed from the vector. This process is done until there are no more nodes in the vector or the nodes that remains are already connected between them.
	
	Third stem:
	If there are still nodes with free degrees, we use existint randomly selected edges as a bridge to connect the nodes that remain free.
	*/

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

			//cout << "sum vale: " << sum << "\n";
			//cout << "Estoy extrayendo vertices de grado " << actualDegree << "\n";
			//cout << "Quedan extraer " << actualDegreeAmount << "\n";

			// Choose randomly an index that representes a node with the degree we are working
			index = actualDegreeStartIndex + (rand() % actualDegreeAmount);
			chosenId = vec[index];

			if (first)
			{
				// If it's the first node, add it to the graph and to thevertexesWithFreeDegrees vector. It always has free degrees
				first = false;
				Vertex* newVertex = new Vertex(chosenId);
				graph.addVertex(newVertex);
				vertexesWithFreeDegrees.push_back(chosenId);
				//cout << "Agrego vertice " << chosenId << "\n";
			}
			else
			{
			
				if (vertexesWithFreeDegrees.size()==0)
				{
					// If the graph is complete before finishing the addition of nodes, the algorithm fails and return the partial graph
					return;
				}
				else
				{
					// Choose a random node from the ones that has free degrees
					existentVertexId = vertexesWithFreeDegrees[rand() % vertexesWithFreeDegrees.size()];
					existentVertex = graph.getVertexById(existentVertexId);
	
					Vertex* newVertex = new Vertex(chosenId);
					graph.addVertex(newVertex);
					graph.addEdge(existentVertex, newVertex);
					//cout << "Agrego vertice " << chosenId << " unido a " << existentVertexId << "\n";
			
					// If new node has free degrees, add it to the vector
					if (openDegrees(newVertex) > 0)
						vertexesWithFreeDegrees.push_back(chosenId);

					// IF the existant node is complete, remove from the vector
					if (openDegrees(existentVertex)==0)
						for(i = 0; i < vertexesWithFreeDegrees.size(); i++)
							if(vertexesWithFreeDegrees[i] == existentVertexId)
								vertexesWithFreeDegrees.erase(vertexesWithFreeDegrees.begin() + i);
				}
			}
			// Delete node from the nodes vector and decrement counters
			vec.erase(vec.begin()+index);
			sum--;
			actualDegreeAmount--;

			//if (actualDegreeAmount==0)
				//cout << "Termine de poner los nodos de grado " << actualDegree << "\n";
		}
		//cout << "Termine de generar todo el grafo!\n";
		// Finish step 1

		// DEBUG: print vector with free degrees nodes
		//printVertexVector(graph, vertexesWithFreeDegrees);

		// With each node, try to connect it's free degrees with the other nodes in the vector
		for (i = 0; i < vertexesWithFreeDegrees.size(); i++)
		{
			v = graph.getVertexById(vertexesWithFreeDegrees[i]);
			//cout << "QUIERO ENCONTRARLE VECINOS A " << vertexesWithFreeDegrees[i] << "\n";
			if (openDegrees(v) > 0)
			{
				for (j = i+1; j < vertexesWithFreeDegrees.size() && openDegrees(v) > 0; j++)
				{
					otherVertex = graph.getVertexById(vertexesWithFreeDegrees[j]);
					if (!v->isNeighbourOf(otherVertex) && openDegrees(otherVertex)>0)
					{
						//cout << "Conecto el vertice " << vertexesWithFreeDegrees[i] << " con el vertice " << vertexesWithFreeDegrees[j] << "\n";
						graph.addEdge(v, otherVertex);
					}
				}
			}
		}
		// DEBUG: print vector with free degrees nodes
		//printVertexVector(graph, vertexesWithFreeDegrees);

		// Step 3
		//cout << "ETAPA 3"<< "\n";
		for (i = 0; i < vertexesWithFreeDegrees.size(); i++) 
				{
					Vertex* VfreeDegrees = graph.getVertexById(vertexesWithFreeDegrees[i]); 
					for (j=1; j<=graph.verticesCount() && openDegrees(VfreeDegrees)>1 ; j++)
					{
						//cout << "Buscando nodos de rewiring para vertice "<<vertexesWithFreeDegrees[i]<<" con "<< openDegrees(graph.getVertexById(vertexesWithFreeDegrees[i]))<< " grados libres\n";
						Vertex* V1Rewiring = graph.getVertexById(j);
						if (vertexesWithFreeDegrees[i]!=j && !V1Rewiring ->isNeighbourOf(VfreeDegrees))
						{
							NeighborsIterator it = V1Rewiring->neighborsIterator(); 
							while (!it.end()) //If a node is selected, we search it's neighbouts
							{
								Vertex* V2Rewiring = *it;
								if(!V2Rewiring ->isNeighbourOf(VfreeDegrees))
								{
										graph.addEdge(V1Rewiring, VfreeDegrees);
										graph.addEdge(V2Rewiring, VfreeDegrees);
										graph.removeEdge(V1Rewiring, V2Rewiring);
										//cout<<"removiendo aristas entre nodos "<<j<<" y "<<V2Rewiring->getVertexId()<<"\n";
										//cout<<"Añadiendo aristas desde los nodos "<<j<<" y "<<V2Rewiring->getVertexId()<<" hacia el nodo "<<vertexesWithFreeDegrees[i]<<"\n";
										//cout<<"\n";
										break;
								}
								it++;
							}
						}
					}
					if (openDegrees(graph.getVertexById(vertexesWithFreeDegrees[i]))==1)
					{
						Vertex* V1freeDegrees = graph.getVertexById(vertexesWithFreeDegrees[i]); 
						NeighborsIterator it = V1freeDegrees->neighborsIterator();
						while (!it.end() && openDegrees(V1freeDegrees)==1)
						{
							Vertex* V2freeDegrees = *it; 
							for (j=1; j<=graph.verticesCount() && openDegrees(V2freeDegrees)==1; j++)
							{
								Vertex* SelectedVertex1 = graph.getVertexById(j); 
								if (vertexesWithFreeDegrees[i]!=j && !SelectedVertex1 ->isNeighbourOf(V1freeDegrees)) 
								{
									NeighborsIterator it2 = SelectedVertex1->neighborsIterator(); 
									while (!it2.end()) 
									{
										Vertex* SelectedVertex2 = *it2; 
										if(!SelectedVertex2 ->isNeighbourOf(V2freeDegrees))
										{
												graph.addEdge(V1freeDegrees, SelectedVertex1);
												graph.addEdge(V2freeDegrees, SelectedVertex2);
												graph.removeEdge(SelectedVertex1, SelectedVertex2);
												//cout<<"Removiendo aristas entre nodos "<<SelectedVertex1->getVertexId()<<" y "<<SelectedVertex2->getVertexId()<<"\n";
												//cout<<"Añadiendo aristas entre los nodos "<<SelectedVertex1->getVertexId()<<"-"<<V1freeDegrees->getVertexId()<<" y "<<SelectedVertex2->getVertexId()<<"-"<<V2freeDegrees->getVertexId()<<"\n";
												//cout<<"\n";
												break;
										}
										it2++;
									}
								}
							}
							it++;
						}
					}
				}
		 // Finish step 3

		vertexesWithFreeDegrees.clear();
		vec.clear();
	}


	// Given a vector with node ids, print for each one it's id, actual degree and free degrees.
	void printVertexVector(Graph& graph, vector<unsigned int> vec)
	{
		Vertex* v;
		for (unsigned int i=0;i<vec.size();i++)
		{
			v = graph.getVertexById(vec[i]);
			cout << "The vertex " << vec[i] << " has " << v->degree() << " neighbours, left " << openDegrees(v) << " degrees\n";
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

