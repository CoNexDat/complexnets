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

    virtual Coefficient clusteringCoefficient(Graph& g, Degree d, bool out, bool in)
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
                clusteringCoefSums += vertexClusteringCoefficient(v, out, in);
            }

            ++it;
        }

        return count == 0 ? 0 : clusteringCoefSums / count;
    }
    
    virtual Coefficient clusteringCoefficient(Graph& g, Degree d)
    {
        return clusteringCoefficient(g, d, false, false);
    }

    virtual Coefficient vertexClusteringCoefficient(Vertex *vertex, bool out, bool in)
    {
        DirectedVertex* directedVertex = static_cast<DirectedVertex*>(vertex);
        
        if (!in && !out)
        {
            // Do out by default
            out = true;
        }
        
        Coefficient outLinks = 0.0;
        Coefficient inLinks = 0.0;

        if (in)
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
                        inLinks += 1.0;
                    }
                    
                    ++inner;
                }
                
                ++outer;
            }           
        }

        if (out)
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
                         outLinks += 1.0;
                     }
                     
                     ++inner;
                 }
                 
                 ++outer;
             }
        }
        
        Coefficient degree = 0.0;
        Coefficient links = 0.0;
        
        if (out && in)
        {
            links = inLinks + outLinks;
            degree = directedVertex->inOutDegree();
        }
        else if (in)
        {
            links = inLinks;
            degree = directedVertex->inDegree();
        }
        else
        {
            links = outLinks;
            degree = directedVertex->outDegree();
        }
        
        if (degree != 0 && degree != 1)
        {
            return links / (degree * (degree - 1));
        }
        
        return 0.0;
    }
    
    // true if a --> b
    static bool isDirectedAdjacent(DirectedVertex *a, DirectedVertex *b)
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
