#ifndef DIRECTED_CLUSTERING_COEFFICIENT_H
#define DIRECTED_CLUSTERING_COEFFICIENT_H

#include "IClusteringCoefficient.h"

namespace graphpp
{

template <class Graph, class Vertex>
class DirectedClusteringCoefficient : public IClusteringCoefficient<Graph, Vertex>
{
public:
    typedef typename graphpp::IClusteringCoefficient<Graph, Vertex>::Coefficient Coefficient;
    typedef typename Graph::VerticesIterator VerticesIterator;
    typedef typename Vertex::VerticesIterator NeighborsIterator;
    typedef typename IClusteringCoefficient<Graph, Vertex>::Degree Degree;

    virtual Coefficient clusteringCoefficient(Graph& g, Degree d, bool positive, bool negative)
    {
        VerticesIterator it = g.verticesIterator();
        unsigned int count = 0;
        Coefficient clusteringCoefSums = 0.0;

        while (!it.end())
        {
            Vertex* v = *it;

            if (v->degree() == d)
            {
                count++;
                clusteringCoefSums += vertexClusteringCoefficient(v, positive, negative);
            }

            ++it;
        }

        return count == 0 ? 0 : clusteringCoefSums / count;
    }
    
    virtual Coefficient clusteringCoefficient(Graph& g, Degree d)
    {
        return clusteringCoefficient(g, d, false, false);
    }

    virtual Coefficient vertexClusteringCoefficient(Vertex *vertex, bool positive, bool negative)
    {
        DirectedVertex* directedVertex = static_cast<DirectedVertex*>(vertex);
        
        if (!negative && !positive)
        {
            // Do positive by default
            positive = true;
        }
        
        Coefficient positiveLinks = 0.0;
        Coefficient negativeLinks = 0.0;

        if (negative)
        {
            NeighborsIterator outer = directedVertex->inNeighborsIterator();
            while (!outer.end())
            {
                DirectedVertex* j = static_cast<DirectedVertex*>(*outer);
                NeighborsIterator inner = directedVertex->inNeighborsIterator();
                while (!inner.end())
                {
                    DirectedVertex* h = static_cast<DirectedVertex*>(*inner);
                    
                    if (isDirectedAdjacent(j, h))
                    {
                        negativeLinks += 1.0;
                    }
                    
                    ++inner;
                }
                
                ++outer;
            }           
        }

        if (positive)
        {
             NeighborsIterator outer = directedVertex->outNeighborsIterator();
             while (!outer.end())
             {
                 DirectedVertex* j = static_cast<DirectedVertex*>(*outer);
                 NeighborsIterator inner = directedVertex->outNeighborsIterator();
                 while (!inner.end())
                 {
                     DirectedVertex* h = static_cast<DirectedVertex*>(*inner);
                     
                     if (isDirectedAdjacent(j, h))
                     {
                         positiveLinks += 1.0;
                     }
                     
                     ++inner;
                 }
                 
                 ++outer;
             }
        }
        
        Coefficient degree = 0.0;
        Coefficient links = 0.0;
        
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
        
        if (degree != 0 && degree != 1)
        {
            return links / (degree * (degree - 1));
        }
        
        return 0.0;
    }
    
    // true if a --> b
    bool isDirectedAdjacent(DirectedVertex *a, DirectedVertex *b)
    {
        NeighborsIterator it = a->outNeighborsIterator();
        while (!it.end())
        {
            DirectedVertex *v = static_cast<DirectedVertex*>(*it);
            if (v->getVertexId() == b->getVertexId())
            {
                return true;
            }
            
            ++it;
        }
        
        return false;
    }
    
    virtual Coefficient vertexClusteringCoefficient(Vertex* vertex)
    {
        return vertexClusteringCoefficient(vertex, false, false);
    }
};
}

#endif
