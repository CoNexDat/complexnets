#ifndef DIRECTED_NEAREST_NEIGHBORS_DEGREE_H
#define DIRECTED_NEAREST_NEIGHBORS_DEGREE_H

#include "INearestNeighborsDegree.h"

namespace graphpp
{
template <class Graph, class Vertex>
class DirectedNearestNeighborsDegree : public INearestNeighborsDegree<Graph, Vertex>
{

public:

    typedef typename graphpp::INearestNeighborsDegree<Graph, Vertex>::MeanDegree MeanDegree;
    typedef typename Vertex::VerticesIterator NeighborsIterator;
    typedef typename Graph::VerticesIterator VerticesIterator;

    virtual MeanDegree meanDegree(Graph& g, typename Vertex::Degree d, bool positive, bool negative)
    {
        VerticesIterator it = g.verticesIterator();
        unsigned int count = 0;
        MeanDegree meanDegreeSums = 0.0;

        while (!it.end())
        {
            Vertex* v = *it;

            if (v->degree() == d)
            {
                ++count;
                meanDegreeSums += meanDegreeForVertex(v, positive, negative);
            }

            ++it;
        }

        return count == 0 ? 0 : meanDegreeSums / count;
    }    
    
    //TODO check if this method is implemented correctly
    virtual MeanDegree meanDegree(Graph& g, typename Vertex::Degree d)
    {
        return meanDegree(g, d, false, false);
    }

    virtual MeanDegree meanDegreeForVertex(Vertex* v, bool positive, bool negative)
    {
        DirectedVertex* directedVertex = static_cast<DirectedVertex*>(v);
        
        if (!positive && !negative)
        {
            // Do positive by default
            positive = true;
        }
       
        MeanDegree positiveLinks = 0.0;
        MeanDegree negativeLinks = 0.0;
        
        if (negative)
        {
            NeighborsIterator it = directedVertex->inNeighborsIterator();
            while (!it.end())
            {                
                negativeLinks += 1.0;
                
                ++it;
            }
        }
        
        if (positive)
        {
            NeighborsIterator it = directedVertex->outNeighborsIterator();
            while (!it.end())
            {                
                positiveLinks += 1.0;
                
                ++it;
            }           
        }
        
        MeanDegree degree = 0.0;
        MeanDegree links = 0.0;
        
        if (positive && negative)
        {
            links = negativeLinks + positiveLinks;
            degree = directedVertex->inOutDegree();
        }
        else if (negative)
        {
            links = negativeLinks;
            degree = directedVertex->inDegree();
        }
        else
        {
            links = positiveLinks;
            degree = directedVertex->outDegree();
        }
        
        if (degree != 0.0) {
            return links / degree;
        }
        
        return 0.0;
    }    
    
    virtual MeanDegree meanDegreeForVertex(Vertex* v)
    {
        return meanDegreeForVertex(v, false, false);
    }
};
}


#endif
