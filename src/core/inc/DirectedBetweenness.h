#pragma once

#include <list>
#include <queue>
#include <stack>
#include <vector>


#include "IBetweenness.h"
#include "mili/mili.h"
#include "typedefs.h"

namespace graphpp
{
template <class Graph, class Vertex>
class DirectedBetweenness : public IBetweenness<Graph, Vertex>
{
public:
    typedef typename IBetweenness<Graph, Vertex>::BetweennessContainer BetweennessContainer;
    typedef typename IBetweenness<Graph, Vertex>::BetweennessIterator BetweennessIterator;

    DirectedBetweenness(DirectedGraph& g)
    {
        initMap(g, (*g.verticesIterator())->getVertexId(), betweenness, 0.0, 0.0);
        calculateBetweenness(g);
    }

    virtual BetweennessIterator iterator()
    {
        return BetweennessIterator(betweenness);
    }

private:
    void calculateBetweenness(DirectedGraph& g)
    {
        auto iter = g.verticesIterator();

        while (!iter.end())
        {
            DirectedVertex* s = *iter;
            std::stack<DirectedVertex*> stack;
            std::queue<DirectedVertex*> queue;
            std::map<typename DirectedVertex::VertexId, std::list<typename Vertex::VertexId>> p;
            std::map<typename DirectedVertex::VertexId, double> sigma;
            std::map<typename DirectedVertex::VertexId, double> d;
            std::map<typename DirectedVertex::VertexId, double> delta;

            initMap(g, s->getVertexId(), sigma, 0.0, 1.0);
            initMap(g, s->getVertexId(), d, -1.0, 0.0);
            initMap(g, s->getVertexId(), delta, 0.0, 0.0);

            queue.push(s);

            while (!queue.empty())
            {
                DirectedVertex* v = queue.front();
                queue.pop();
                stack.push(v);

                // iterate through v's neighbors
                auto neighbourIter = v->outNeighborsIterator();

                while (!neighbourIter.end())
                {
                    Vertex* w = (Vertex*)*neighbourIter;
                    // w found for the first time?
                    double wValue = d[w->getVertexId()];
                    // double vValue = d[v->getVertexId()];
                    if (wValue < 0)
                    {
                        queue.push(w);
                        d[w->getVertexId()] = d[v->getVertexId()] + 1;
                    }
                    // shortest path to w via v?
                    if (d[w->getVertexId()] == (d[v->getVertexId()] + 1))
                    {
                        sigma[w->getVertexId()] = sigma[w->getVertexId()] + sigma[v->getVertexId()];
                        p[w->getVertexId()].push_back(v->getVertexId());
                    }

                    ++neighbourIter;
                }
            }

            // S returns vertices in order of non-increasing distance from s
            while (!stack.empty())
            {
                Vertex* w = stack.top();
                stack.pop();

                std::list<typename Vertex::VertexId> vertices = p[w->getVertexId()];

                for (const auto& v : vertices)
                {
                    delta[v] = delta[v] + ((1 + delta[w->getVertexId()]) *
                                           (sigma[v] / sigma[w->getVertexId()]));
                }

                if (w->getVertexId() != s->getVertexId())
                {
                    betweenness[w->getVertexId()] += delta[w->getVertexId()];
                }
            }

            ++iter;
        }
    }

    void initMap(
        DirectedGraph& g,
        unsigned int vertexId,
        std::map<typename Vertex::VertexId, double>& m,
        double commonValue,
        double distinguishedValue)
    {
        auto it = g.verticesIterator();

        // initialize all elements in zero, except for the current vertex
        while (!it.end())
        {
            Vertex* v = *it;
            m.insert(std::pair<typename Vertex::VertexId, double>(v->getVertexId(), commonValue));
            ++it;
        }
        // modify the value associated to key 'vertexId'
        m[vertexId] = distinguishedValue;
    }

    BetweennessContainer betweenness;
};
}  // namespace graphpp
