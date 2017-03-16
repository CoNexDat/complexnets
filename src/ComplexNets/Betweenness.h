#ifndef BETWEENNESS_H
#define BETWEENNESS_H
#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "IBetweenness.h"
#include "mili/mili.h"

namespace graphpp
{
template <class Graph, class Vertex>
class Betweenness : public IBetweenness<Graph, Vertex>
{
public:
    typedef typename IBetweenness<Graph, Vertex>::BetweennessContainer BetweennessContainer;
    typedef typename IBetweenness<Graph, Vertex>::BetweennessIterator BetweennessIterator;
    typedef typename Graph::VerticesIterator VerticesIterator;
    typedef typename Vertex::VerticesIterator NeighbourIterator;

    Betweenness(Graph& g)
    {
        initMap(g, 1, betweenness, 0.0, 0.0);
        calculateBetweenness(g);
    }

    virtual BetweennessIterator iterator()
    {
        return BetweennessIterator(betweenness);
    }

private:
    void calculateBetweenness(Graph& g)
    {
        VerticesIterator iter = g.verticesIterator();

        while (!iter.end())
        {
            Vertex* s = *iter;
            std::stack<Vertex*> stack;
            std::queue<Vertex*> queue;
            std::map<typename Vertex::VertexId, std::list<typename Vertex::VertexId>> p;
            std::map<typename Vertex::VertexId, double> sigma;
            std::map<typename Vertex::VertexId, double> d;
            std::map<typename Vertex::VertexId, double> delta;

            initMap(g, s->getVertexId(), sigma, 0.0, 1.0);
            initMap(g, s->getVertexId(), d, -1.0, 0.0);
            initMap(g, s->getVertexId(), delta, 0.0, 0.0);

            queue.push(s);

            while (!queue.empty())
            {
                Vertex* v = queue.front();
                queue.pop();
                stack.push(v);

                // iterate through v's neighbors
                NeighbourIterator neighbourIter = v->neighborsIterator();

                while (!neighbourIter.end())
                {
                    Vertex* w = *neighbourIter;
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
                typename std::list<typename Vertex::VertexId>::iterator it;

                for (it = vertices.begin(); it != vertices.end(); ++it)
                {
                    typename Vertex::VertexId v = *it;
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

    void initMap(Graph& g,
                 unsigned int vertexId,
                 std::map<typename Vertex::VertexId, double>& m,
                 double commonValue,
                 double distinguishedValue)
    {
        VerticesIterator it = g.verticesIterator();

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
}

#endif
