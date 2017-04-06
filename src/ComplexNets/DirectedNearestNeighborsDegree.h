#pragma once

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

    virtual MeanDegree meanDegree(Graph& g, typename Vertex::Degree d, bool out, bool in)
    {
        VerticesIterator it = g.verticesIterator();
        unsigned int count = 0;
        MeanDegree meanDegreeSums = 0.0;

        if (!in && !out)
        {
            std::cout << "Warning: DirectedNearestNeighborsDegree::meanDegree no direction given.\n";
        }

        while (!it.end())
        {
            Vertex* v = *it;

            if (v->degree() == d)
            {
                ++count;
                meanDegreeSums += meanDegreeForVertex(v, out, in);
            }

            ++it;
        }

        return count == 0 ? 0 : meanDegreeSums / count;
    }

    // TODO check if this method is implemented correctly
    virtual MeanDegree meanDegree(Graph& g, typename Vertex::Degree d)
    {
        return meanDegree(g, d, false, false);
    }

    virtual MeanDegree meanDegreeForVertex(Vertex* v, bool out, bool in)
    {
        DirectedVertex* directedVertex = static_cast<DirectedVertex*>(v);

        if (!out && !in)
        {
            // Do out by default
            out = true;
        }

        MeanDegree outLinks = 0.0;
        MeanDegree inLinks = 0.0;

        if (in)
        {
            NeighborsIterator it = directedVertex->inNeighborsIterator();
            while (!it.end())
            {
                DirectedVertex* vertex = static_cast<DirectedVertex*>(*it);
                inLinks += vertex->inDegree();

                ++it;
            }
        }

        if (out)
        {
            NeighborsIterator it = directedVertex->outNeighborsIterator();
            while (!it.end())
            {
                DirectedVertex* vertex = static_cast<DirectedVertex*>(*it);
                outLinks += vertex->outDegree();

                ++it;
            }
        }

        MeanDegree degree = 0.0;
        MeanDegree links = 0.0;

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

        if (degree != 0.0)
        {
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
