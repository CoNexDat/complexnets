#pragma once

#include "IMaxClique.h"
#include "TraverserOrdered.h"
#include "mili/mili.h"

#include <time.h>

namespace graphpp
{
template <class Graph, class Vertex>
class MaxClique;

template <class Graph, class Vertex>
class MaxCliqueVisitor
{
public:
    MaxCliqueVisitor(MaxClique<Graph, Vertex>& observer) : maxCliqueObserver(observer)
    {
    }

    bool visitVertex(Vertex* vertex)
    {
        maxCliqueObserver.visit(vertex);
        return true;
    }

private:
    MaxClique<Graph, Vertex>& maxCliqueObserver;
};

template <class Graph, class Vertex>
class MaxCliqueMap
{
public:
    MaxCliqueMap(MaxClique<Graph, Vertex>& observer) : maxCliqueObserver(observer)
    {
    }

    int get(Vertex* vertex)
    {
        return maxCliqueObserver.getMaxCliqueSize(vertex);
    }

private:
    MaxClique<Graph, Vertex>& maxCliqueObserver;
};

class DegreeCompare
{
public:
    bool operator()(const Vertex* v1, const Vertex* v2)
    {
        return v1->degree() > v2->degree();
    }
};

template <class Graph, class Vertex>
class MaxClique : public IMaxClique<Graph, Vertex>
{
public:
    typedef std::map<typename Vertex::VertexId, typename std::list<int>*> MaxCliqueContainer;
    typedef AutonomousIterator<MaxCliqueContainer> MaxCliqueIterator;
    typedef typename Vertex::VerticesIterator NeighborsIterator;
    typedef typename std::list<Vertex*> L_type;
    typedef typename L_type::iterator L_iterator;
    typedef typename std::map<Vertex*, L_type*> a_type;
    typedef typename a_type::iterator a_iterator;
    typedef typename std::map<Vertex*, a_type*> as_type;
    typedef typename as_type::iterator as_iterator;

    MaxClique(Graph& graph)
    {
        calculateMaxClique(graph);
    }

    virtual MaxCliqueIterator iterator()
    {
        return MaxCliqueIterator(container);
    }

    virtual bool finished()
    {
        return true;
    }

    void visit(Vertex* v)
    {
        auto it1 = v->neighborsIterator();

        while (!it1.end())
        {
            Vertex* x = *it1;
            if (x->getVisited())
            {
                NeighborsIterator it2 = v->neighborsIterator();
                while (!it2.end())
                {
                    Vertex* i = *it2;
                    if (i->getVisited())
                    {
                        L_type* L = new L_type();

                        if (as[x] == nullptr || (*as[x])[i] == nullptr)
                        {
                            L->push_back(x);
                            L->push_back(v);
                        }
                        else
                        {
                            NeighborsIterator iterator1 = v->neighborsIterator();
                            while (!iterator1.end())
                            {
                                L_iterator iterator2 = (*as[x])[i]->begin();
                                while (iterator2 != (*as[x])[i]->end())
                                {
                                    if ((*iterator1)->getVertexId() == (*iterator2)->getVertexId())
                                    {
                                        L->push_back(*iterator1);
                                    }
                                    iterator2++;
                                }
                                iterator1++;
                            }
                            L->push_back(v);
                        }
                        if (as[v] == nullptr)
                        {
                            as[v] = new a_type();
                        }
                        if (as[x] == nullptr)
                        {
                            as[x] = new a_type();
                        }
                        if ((*as[x])[v] == nullptr)
                        {
                            (*as[x])[v] = L;
                            (*as[v])[x] = L;
                        }
                        else if (L->size() >= (*as[v])[x]->size())
                        {
                            delete (*as[v])[x];
                            (*as[x])[v] = L;
                            (*as[v])[x] = L;
                        }
                        else
                        {
                            delete L;
                        }
                    }
                    it2++;
                }
            }
            it1++;
        }
    }

    int getMaxCliqueSize(Vertex* vertex)
    {
        unsigned int max_size = 0;
        std::list<int>* ids = new std::list<int>();
        for (a_iterator iterator2 = as[vertex]->begin(); iterator2 != as[vertex]->end();
             iterator2++)
        {
            if ((*iterator2).second && (*iterator2).second->size() > max_size)
            {
                max_size = (*iterator2).second->size();
                delete ids;
                ids = new std::list<int>();

                for (L_iterator it = (*iterator2).second->begin(); it != (*iterator2).second->end();
                     it++)
                {
                    ids->push_back((*it)->getVertexId());
                }
            }
        }
        container[vertex->getVertexId()] = ids;

        return max_size;
    }

    virtual std::list<int> getMaxCliqueList()
    {
        unsigned int max_size = 0;
        std::list<int>* ids = nullptr;
        for (auto iterator1 = MaxCliqueIterator(container); !iterator1.end(); iterator1++)
        {
            if (iterator1->second->size() > max_size)
            {
                max_size = iterator1->second->size();
                ids = (iterator1->second);
            }
        }

        return *ids;
    }

    virtual DistributionIterator distIterator()
    {
        return distribution.iterator();
    }

private:
    void calculateMaxClique(Graph& graph)
    {
        MaxCliqueVisitor<Graph, Vertex> visitor(*this);
        TraverserOrdered<Graph, Vertex, MaxCliqueVisitor<Graph, Vertex>, DegreeCompare>::traverse(
            graph, visitor, DegreeCompare());

        MaxCliqueMap<Graph, Vertex> map(*this);
        distribution.calculateDistribution(graph, &map);
    }

    as_type as;
    MaxCliqueContainer container;
    IntegerDistribution<Graph, Vertex, MaxCliqueMap<Graph, Vertex>> distribution;
};

//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
//************************************ EXACT ********************************************//
template <class Graph, class Vertex>
class MaxCliqueExact;

template <class Graph, class Vertex>
class MaxCliqueExactVisitor
{
public:
    MaxCliqueExactVisitor(MaxCliqueExact<Graph, Vertex>& observer) : maxCliquenObserver(observer)
    {
    }

    bool visitVertex(Vertex* vertex)
    {
        maxCliquenObserver.visit(vertex);

        if ((time(NULL) - maxCliquenObserver.start) > maxCliquenObserver.maxTime)
        {
            maxCliquenObserver.timeouted = true;
            return false;
        }
        return true;
    }

private:
    MaxCliqueExact<Graph, Vertex>& maxCliquenObserver;
};

template <class Graph, class Vertex>
class MaxCliqueExactMap
{
public:
    MaxCliqueExactMap(MaxCliqueExact<Graph, Vertex>& observer) : maxCliqueObserver(observer)
    {
    }

    int get(Vertex* vertex)
    {
        return maxCliqueObserver.getMaxCliqueSize(vertex);
    }

private:
    MaxCliqueExact<Graph, Vertex>& maxCliqueObserver;
};

template <class Graph, class Vertex>
class MaxCliqueExact : public IMaxClique<Graph, Vertex>
{
public:
    typedef std::map<typename Vertex::VertexId, typename std::list<int>*> MaxCliqueContainer;
    typedef AutonomousIterator<MaxCliqueContainer> MaxCliqueIterator;
    typedef typename Vertex::VerticesIterator NeighborsIterator;
    typedef typename std::list<Vertex*> L_type;
    typedef typename L_type::iterator L_iterator;
    typedef typename std::list<L_type*> a_type;
    typedef typename a_type::iterator a_iterator;
    typedef typename std::map<Vertex*, a_type*> as_type;
    typedef typename as_type::iterator as_iterator;

    MaxCliqueExact(Graph& graph, int max_time)
        : maxTime(max_time), timeouted(false), start(time(NULL))
    {
        calculateMaxClique(graph);
    }

    virtual MaxCliqueIterator iterator()
    {
        return MaxCliqueIterator(container);
    }

    virtual bool finished()
    {
        return !timeouted;
    }

    /*void visit(Vertex* v){

    }*/

    void visit(Vertex* v)
    {
        for (auto it1 = v->neighborsIterator(); !it1.end(); it1++)
        {
            if ((time(NULL) - start) > maxTime)
            {
                return;
            }

            Vertex* x = *it1;
            if (x->getVisited())
            {
                if (as[x] == nullptr)
                {
                    as[x] = new a_type();
                    bool _new = false;
                    bool _old = false;
                    L_type* L = new L_type();
                    L->push_back(x);
                    L->push_back(v);

                    if (as[v] == nullptr)
                    {
                        as[v] = new a_type();
                        _new = true;
                    }
                    else
                        for (a_iterator it3 = as[v]->begin(); it3 != as[v]->end(); it3++)
                        {
                            L_type* B = (*it3);
                            if (B->size() < L->size())
                            {
                                if (include(B, L))
                                {
                                    it3 = as[v]->erase(it3);
                                }
                                _new = true;
                            }
                            else
                            {
                                if (!include(L, B))
                                {
                                    _new = true;
                                }
                                else
                                {
                                    _old = true;
                                }
                            }
                        }

                    if (_new && !_old)
                    {
                        for (L_iterator itF = L->begin(); itF != L->end(); itF++)
                        {
                            as[(*itF)]->push_back(L);
                        }
                    }
                }
                else
                    for (a_iterator it2 = as[x]->begin(); it2 != as[x]->end(); it2++)
                    {
                        L_type* A = (*it2);
                        bool _new = false;
                        bool _old = false;

                        L_type* L = new L_type();
                        NeighborsIterator iterator1 = v->neighborsIterator();
                        while (!iterator1.end())
                        {
                            L_iterator iterator2 = A->begin();
                            while (iterator2 != A->end())
                            {
                                if ((*iterator1)->getVertexId() == (*iterator2)->getVertexId())
                                {
                                    L->push_back(*iterator1);
                                }
                                iterator2++;
                            }
                            iterator1++;
                        }
                        L->push_back(v);

                        if (as[v] == nullptr)
                        {
                            as[v] = new a_type();
                            _new = true;
                        }
                        else
                            for (a_iterator it3 = as[v]->begin(); it3 != as[v]->end(); it3++)
                            {
                                L_type* B = (*it3);
                                if (B->size() < L->size())
                                {
                                    if (include(B, L))
                                    {
                                        it3 = as[v]->erase(it3);
                                    }
                                    _new = true;
                                }
                                else
                                {
                                    if (!include(L, B))
                                    {
                                        _new = true;
                                    }
                                    else
                                    {
                                        _old = true;
                                    }
                                }
                            }

                        if (_new && !_old)
                        {
                            for (L_iterator itF = L->begin(); itF != L->end(); itF++)
                            {
                                as[(*itF)]->push_back(L);
                            }
                        }
                    }
            }
        }
    }

    int getMaxCliqueSize(Vertex* vertex)
    {
        unsigned int max_size = 0;
        std::list<int>* ids = new std::list<int>();
        for (a_iterator iterator2 = as[vertex]->begin(); iterator2 != as[vertex]->end();
             iterator2++)
        {
            if ((*iterator2) && (*iterator2)->size() > max_size)
            {
                max_size = (*iterator2)->size();
                delete ids;
                ids = new std::list<int>();
                for (L_iterator iterator10 = (*iterator2)->begin();
                     iterator10 != (*iterator2)->end(); iterator10++)
                {
                    ids->push_back((*iterator10)->getVertexId());
                }
            }
        }

        container[vertex->getVertexId()] = ids;

        return max_size;
    }

    virtual std::list<int> getMaxCliqueList()
    {
        unsigned int max_size = 0;
        std::list<int>* ids = nullptr;
        for (MaxCliqueIterator iterator1 = MaxCliqueIterator(container); !iterator1.end();
             iterator1++)
        {
            if (iterator1->second->size() > max_size)
            {
                max_size = iterator1->second->size();
                ids = (iterator1->second);
            }
        }

        return *ids;
    }

    virtual DistributionIterator distIterator()
    {
        return distribution.iterator();
    }

private:
    bool include(L_type* B, L_type* A)
    {
        for (L_iterator iterator1 = B->begin(); iterator1 != B->end(); iterator1++)
        {
            bool cont = false;
            for (L_iterator iterator2 = A->begin(); iterator2 != A->end(); iterator2++)
            {
                if ((*iterator1)->getVertexId() == (*iterator2)->getVertexId())
                {
                    cont = true;
                }
            }
            if (!cont)
            {
                return false;
            }
        }
        return true;
    }

    void calculateMaxClique(Graph& graph)
    {
        MaxCliqueExactVisitor<Graph, Vertex> visitor(*this);
        TraverserOrdered<Graph, Vertex, MaxCliqueExactVisitor<Graph, Vertex>, DegreeCompare>::
            traverse(graph, visitor, DegreeCompare());

        if (!timeouted)
        {
            MaxCliqueExactMap<Graph, Vertex> map(*this);
            distribution.calculateDistribution(graph, &map);
        }
    }

    as_type as;
    MaxCliqueContainer container;
    IntegerDistribution<Graph, Vertex, MaxCliqueExactMap<Graph, Vertex>> distribution;

public:
    int maxTime;
    bool timeouted;
    int start;
};
}
/*
        linea de commandos
        tiempo para exacto
*/
