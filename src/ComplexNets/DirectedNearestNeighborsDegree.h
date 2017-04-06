#pragma once

#include "INearestNeighborsDegree.h"

namespace graphpp
{
template <class Graph, class Vertex>
class DirectedNearestNeighborsDegree : public INearestNeighborsDegree<Graph, Vertex>
{
public:
    virtual double meanDegree(Graph& g, typename Vertex::Degree d, bool out, bool in)
    {
        auto it = g.verticesIterator();
        unsigned int count = 0;
        double meanDegreeSums = 0.0;

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
    virtual double meanDegree(Graph& g, typename Vertex::Degree d)
    {
        return meanDegree(g, d, false, false);
    }

    virtual double meanDegreeForVertex(Vertex* v, bool out, bool in)
    {
        DirectedVertex* directedVertex = static_cast<DirectedVertex*>(v);

        if (!out && !in)
        {
            // Do out by default
            out = true;
        }

        double outLinks = 0.0;
        double inLinks = 0.0;

        if (in)
        {
            auto it = directedVertex->inNeighborsIterator();
            while (!it.end())
            {
                DirectedVertex* vertex = static_cast<DirectedVertex*>(*it);
                inLinks += vertex->inDegree();

                ++it;
            }
        }

        if (out)
        {
            auto it = directedVertex->outNeighborsIterator();
            while (!it.end())
            {
                DirectedVertex* vertex = static_cast<DirectedVertex*>(*it);
                outLinks += vertex->outDegree();

                ++it;
            }
        }

        double degree = 0.0;
        double links = 0.0;

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

    virtual double meanDegreeForVertex(Vertex* v)
    {
        return meanDegreeForVertex(v, false, false);
    }
};
}
