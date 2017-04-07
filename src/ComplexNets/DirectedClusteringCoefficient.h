#pragma once

#include "IClusteringCoefficient.h"
#include "typedefs.h"

namespace graphpp
{
template <class Graph, class Vertex>
class DirectedClusteringCoefficient : public IClusteringCoefficient<Graph, Vertex>
{
public:
    virtual double clusteringCoefficient(Graph& g, unsigned int d, bool out, bool in)
    {
        auto it = g.verticesIterator();
        unsigned int count = 0;
        double clusteringCoefSums = 0.0;

        if (!in && !out)
        {
            std::cout << "Warning: DirectedClusteringCoefficient::clusteringCoefficient no "
                         "direction given.\n";
        }

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

    virtual double clusteringCoefficient(Graph& g, unsigned int d)
    {
        return clusteringCoefficient(g, d, false, false);
    }

    virtual double vertexClusteringCoefficient(Vertex* vertex, bool out, bool in)
    {
        DirectedVertex* directedVertex = static_cast<DirectedVertex*>(vertex);

        if (!in && !out)
        {
            // Do out by default
            out = true;
        }

        double outLinks = 0.0;
        double inLinks = 0.0;

        if (in)
        {
            auto outer = directedVertex->inNeighborsIterator();
            while (!outer.end())
            {
                DirectedVertex* j = static_cast<DirectedVertex*>(*outer);

                auto inner = directedVertex->inNeighborsIterator();
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
            auto outer = directedVertex->outNeighborsIterator();
            while (!outer.end())
            {
                DirectedVertex* j = static_cast<DirectedVertex*>(*outer);

                auto inner = directedVertex->outNeighborsIterator();
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

        if (degree != 0 && degree != 1)
        {
            return links / (degree * (degree - 1));
        }

        return 0.0;
    }

    // true if a --> b
    static bool isDirectedAdjacent(DirectedVertex* a, DirectedVertex* b)
    {
        auto it = a->outNeighborsIterator();
        while (!it.end())
        {
            DirectedVertex* v = static_cast<DirectedVertex*>(*it);
            if (v->getVertexId() == b->getVertexId())
            {
                return true;
            }

            ++it;
        }

        return false;
    }

    virtual double vertexClusteringCoefficient(Vertex* vertex)
    {
        return vertexClusteringCoefficient(vertex, false, false);
    }
};
}
