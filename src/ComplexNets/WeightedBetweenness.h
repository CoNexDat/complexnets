#ifndef WEIGHTEDBETWEENNESS_H
#define WEIGHTEDBETWEENNESS_H
#include <list>
#include <queue>
#include <stack>
#include <vector>

#include "IBetweenness.h"
#include "mili/mili.h"

namespace graphpp
{
class BrandesNodeComparatorLargerFirst
{
public:
    bool operator()(graphpp::WeightedVertexAspect<graphpp::AdjacencyListVertex>* v1,
                    graphpp::WeightedVertexAspect<graphpp::AdjacencyListVertex>* v2)
    {
        if (v1->distance < v2->distance)
        {
            return true;
        }
        return false;
    }
};

class BrandesNodeComparatorSmallerFirst
{
public:
    bool operator()(graphpp::WeightedVertexAspect<graphpp::AdjacencyListVertex>* v1,
                    graphpp::WeightedVertexAspect<graphpp::AdjacencyListVertex>* v2)
    {
        if (v1->distance > v2->distance)
        {
            return true;
        }
        return false;
    }
};

template <class Graph, class Vertex>
class WeightedBetweenness : public IBetweenness<Graph, Vertex>
{
public:
    typedef typename IBetweenness<Graph, Vertex>::BetweennessContainer BetweennessContainer;
    typedef typename IBetweenness<Graph, Vertex>::BetweennessIterator BetweennessIterator;
    typedef typename Graph::VerticesIterator VerticesIterator;
    typedef typename Vertex::VerticesIterator NeighbourIterator;

    WeightedBetweenness(Graph& g)
    {
        initMap(g, 1, betweenness, 0.0, 0.0);
        calculateBetweenness(g);
    }

    virtual BetweennessIterator iterator()
    {
        return BetweennessIterator(betweenness);
    }

private:
    double const inf = 1.0 / 0.0;

    void calculateBetweenness(Graph& g)
    {
        VerticesIterator iter = g.verticesIterator();
        int n = g.verticesCount();
        int i = 1;
        while (!iter.end())
        {
            Vertex* s = *iter;
            std::priority_queue<Vertex*, std::vector<Vertex*>, BrandesNodeComparatorLargerFirst> S;
            std::priority_queue<Vertex*, std::vector<Vertex*>, BrandesNodeComparatorSmallerFirst> Q;
            std::map<typename Vertex::VertexId, std::list<typename Vertex::VertexId>> p;
            std::map<typename Vertex::VertexId, double> sigma;
            std::map<typename Vertex::VertexId, double> d;
            std::map<typename Vertex::VertexId, double> delta;

            initMap(g, s->getVertexId(), sigma, 0.0, 1.0);
            initMap(g, s->getVertexId(), delta, 0.0, 0.0);
            initDistances(g, inf);
            s->distance = 0.0;

            Q.push(s);

            while (!Q.empty())
            {
                // printPQ(Q);
                Vertex* v = Q.top();
                Q.pop();
                S.push(v);

                // iterate through v's neighbors
                NeighbourIterator neighbourIter = v->neighborsIterator();

                while (!neighbourIter.end())
                {
                    Vertex* w = static_cast<Vertex*>(*neighbourIter);
                    double alt = v->distance + v->edgeWeight(w);
                    double wValue = w->distance;

                    if (alt < wValue)
                    {
                        w->distance = alt;
                        // refreshing ordering of priority queues
                        std::make_heap(const_cast<Vertex**>(&Q.top()),
                                       const_cast<Vertex**>(&Q.top()) + Q.size(),
                                       BrandesNodeComparatorSmallerFirst());
                        std::make_heap(const_cast<Vertex**>(&S.top()),
                                       const_cast<Vertex**>(&S.top()) + S.size(),
                                       BrandesNodeComparatorLargerFirst());
                        if (wValue == inf)
                        {
                            Q.push(w);
                        }
                        sigma[w->getVertexId()] = 0.0;
                        p[w->getVertexId()].clear();
                        ;
                    }
                    // shortest path to w via v?
                    if (w->distance == alt)
                    {
                        sigma[w->getVertexId()] = sigma[w->getVertexId()] + sigma[v->getVertexId()];
                        p[w->getVertexId()].push_back(v->getVertexId());
                    }

                    ++neighbourIter;
                }
            }

            while (!S.empty())
            {
                Vertex* w = S.top();
                S.pop();

                std::list<typename Vertex::VertexId> vertices = p[w->getVertexId()];
                typename std::list<typename Vertex::VertexId>::iterator it;

                for (it = vertices.begin(); it != vertices.end(); ++it)
                {
                    typename Vertex::VertexId v = *it;
                    double c =
                        (sigma[v] / sigma[w->getVertexId()]) * (1.0 + delta[w->getVertexId()]);
                    delta[v] = delta[v] + c;
                }

                if (w->getVertexId() != s->getVertexId())
                {
                    betweenness[w->getVertexId()] += delta[w->getVertexId()];
                }
            }

            printf("Progress: %.2f% \n", (double)i / (double)n * 100.0);

            ++iter;
            ++i;
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

    void initDistances(Graph& g, double commonValue)
    {
        VerticesIterator it = g.verticesIterator();
        while (!it.end())
        {
            Vertex* v = *it;
            v->distance = commonValue;
            ++it;
        }
    }

    void printPQ(std::priority_queue<
                 graphpp::WeightedVertexAspect<graphpp::AdjacencyListVertex>*,
                 std::vector<
                     graphpp::WeightedVertexAspect<graphpp::AdjacencyListVertex>*,
                     std::allocator<graphpp::WeightedVertexAspect<graphpp::AdjacencyListVertex>*>>,
                 graphpp::BrandesNodeComparatorSmallerFirst>& S)
    {
        std::priority_queue<
            graphpp::WeightedVertexAspect<graphpp::AdjacencyListVertex>*,
            std::vector<
                graphpp::WeightedVertexAspect<graphpp::AdjacencyListVertex>*,
                std::allocator<graphpp::WeightedVertexAspect<graphpp::AdjacencyListVertex>*>>,
            graphpp::BrandesNodeComparatorSmallerFirst>
            pq = S;
        printf("[ ");
        while (!pq.empty())
        {
            Vertex* v = pq.top();
            printf("id: %d - dist: %f /", v->getVertexId(), v->distance);
            pq.pop();
        }
        printf("] \n ");
    }

    void printPS(std::priority_queue<
                 graphpp::WeightedVertexAspect<graphpp::AdjacencyListVertex>*,
                 std::vector<
                     graphpp::WeightedVertexAspect<graphpp::AdjacencyListVertex>*,
                     std::allocator<graphpp::WeightedVertexAspect<graphpp::AdjacencyListVertex>*>>,
                 graphpp::BrandesNodeComparatorLargerFirst>& S)
    {
        std::priority_queue<
            graphpp::WeightedVertexAspect<graphpp::AdjacencyListVertex>*,
            std::vector<
                graphpp::WeightedVertexAspect<graphpp::AdjacencyListVertex>*,
                std::allocator<graphpp::WeightedVertexAspect<graphpp::AdjacencyListVertex>*>>,
            graphpp::BrandesNodeComparatorLargerFirst>
            pq = S;
        printf("[ ");
        while (!pq.empty())
        {
            Vertex* v = pq.top();
            printf("id: %d ;dist: %f , \n", v->getVertexId(), v->distance);
            pq.pop();
        }
        printf("\n] \n ");
    }

    BetweennessContainer betweenness;
};
}

#endif
