#ifndef CONEXITYVERIFIER_H
#define CONEXITYVERIFIER_H

#include <vector>
#include "mili/mili.h"
#include "TraverserBFS.h"

namespace graphpp
{


//template <class Graph, class Vertex>
//class ConexityVerifier;


template <class Graph, class Vertex>
class ConexityVisitor
{
public:
	std::vector<unsigned int> vertexesLeft;
    std::vector<unsigned int> vertexesInComponent;

	/*
    ConexityVisitor(ConexityVerifier<Graph, Vertex>& observer)
        : conexityVerifierObserver(observer) {}
	*/
    /**
    * Method: visitVertex
    * -------------------
    * Description: Action invoked by Traverser when a node is reached. The goal of
    * the visitVertex method is to notify the ConexityVerifier class about the vertex/
    * @returns true if iterator should keep traversing
    */
    bool visitVertex(Vertex* vertex)
    {
		return true;    	
		/*vertexesInComponent.push_back(id);
		for(int i = 0; i < vertexesLeft.size(); i++)
		{
			if(vertexesLeft[i] == id)
			{
				vertexesLeft.erase(i);
				return;
			}
		} */      

		//conexityVerifierObserver.visited(vertex->getVertexId());
        //return true;
    }
/*
private:

    ConexityVerifier<Graph, Vertex>& conexityVerifierObserver;
*/
};


/*

template <class Graph, class Vertex>
class ConexityVerifier
{
public:
 
	//typedef graphpp::AdjacencyListGraph<graphpp::AdjacencyListVertex>::VerticesIterator VerticesIterator;
	

    void visited(int id)
    {
    	vertexesInComponent.push_back(id);
		for(int i = 0; i < vertexesLeft.size(); i++)
		{
			if(vertexesLeft[i] == id)
			{
				vertexesLeft.erase(i);
				return;
			}
		}
    }


    void getBigestComponent(Graph& graph)
    {
		VerticesIterator it = graph.verticesIterator();
        while (!it.end())
        {
            vertexesLeft.push_back(it->getVertexId());
            ++it;
        }
		

        ConexityVisitor<Graph, Vertex> visitor(*this);
		do
		{
			vertexesInComponent.clear();
			Vertex* source = graph.getVertexById(vertexesLeft.back());
			graph.getVertexById(vertexesLeft.pop_back()
			TraverserBFS<Graph, Vertex, ConexityVisitor<Graph, Vertex> >::traverse(source, visitor);			
		} while(vertexesLeft.size() > 0 && vertexesInComponent.size() < graph.verticesCount()/2);


		it = graph.verticesIterator();
        while (!it.end())
        {
			bool found = false;
            for(int i = 0; i < vertexesInComponent.size(); i++)
			{
				if(vertexesInComponent[i] == it->getVertexId())
				{
					found = true;
					break;
				}
			}
			if(!found)
				graph.removeVertex(it);
				
            ++it;
        }
		
    }


};
*/
}


#endif
