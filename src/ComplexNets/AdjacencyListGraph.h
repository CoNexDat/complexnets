// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

#pragma once

#include <algorithm>
#include <climits>
#include <iostream>
#include <memory>
#include "GraphExceptions.h"
#include "mili/mili.h"

namespace graphpp
{
/**
 * Class: VertexComparator
 * ------------
 * Functor to provide custom vertex comparation in containers
 */
template <class T>
class VertexComparator
{
public:
    bool operator()(T* v1, T* v2) const
    {
        return v1->getVertexId() < v2->getVertexId();
    }
};

/**
 * Class: VertexFinder
 * ------------
 * Base abstraction to find vertex in containers. Used for Vector and List
 */
template <class Vertex, class Container>
class VertexFinder
{
public:
    static Vertex* find(typename Vertex::VertexId id, const Container& c)
    {
        auto v = std::find_if(begin(c), end(c), [id](auto v) { return v->getVertexId() == id; });

        if (v != end(c))
            return *v;

        return nullptr;
    }
};

/**
 * Class: VertexFinder
 * ------------
 * Template specialization of VertexFinder used to search vertices
 * more efficiently in sets.
 */
template <class Vertex>
class VertexFinder<Vertex, std::set<Vertex*, VertexComparator<Vertex>>>
{
public:
    static Vertex* find(
        typename Vertex::VertexId id, const std::set<Vertex*, VertexComparator<Vertex>>& c)
    {
        auto prototype = std::make_unique<Vertex>(id);
        auto v = c.find(prototype.get());

        if (v != end(c))
            return *v;

        return nullptr;
    }
};

/**
 * Class: Graph
 * ------------
 * Description: Principal graph class. Allows to add vertices and edges, and provides
 * iterators to work with them.
 * Template Argument Vertex: Type of the vertex. Vertex should have an addEdge method that
 * receives another Vertex
 * Template Argument VertexContainer: Container that will hold the vertices. May be
 * std::list<Vertex>, std::vector<Vertex> or std::set<Vertex>, depending on the user's
 * preferences
 */
template <class Vertex, class VertexContainer = std::set<Vertex*, VertexComparator<Vertex>>>
class AdjacencyListGraph
{
public:
    using VerticesConstIterator = CAutonomousIterator<VertexContainer>;
    using VerticesIterator = AutonomousIterator<VertexContainer>;
    using NeighborsIterator = typename Vertex::VerticesIterator;
    using VertexId = typename Vertex::VertexId;

    AdjacencyListGraph(const bool isDigraph = false, const bool isMultigraph = false)
    {
        this->_isDigraph = isDigraph;
        this->_isMultigraph = isMultigraph;
    }

    ~AdjacencyListGraph()
    {
        auto it = verticesConstIterator();
        while (!it.end())
        {
            delete *it;
            ++it;
        }
    }

    /**
     * Method: addVertex
     * -----------------
     * Description: Adds a vertex to the graph
     * @param v Vertex to be added
     */
    void addVertex(Vertex* v)
    {
        // insert the vertex in the vertices container
        insert_into(vertices, v);
    }

    /**
     * Method: removeVertex
     * -----------------
     * Description: Removes a vertex and all of its edge of the graph
     * @param v Vertex to be added
     */
    void removeVertex(Vertex* v)
    {
        auto it = v->neighborsIterator();

        while (!it.end())
        {
            Vertex* neighbour = *it;
            removeEdge(neighbour, v);
            it++;
        }
        // removes the vertex from the vertices container
        remove_first_from(vertices, v);
    }

    /**
     * Method: addEdge
     * ---------------
     * Description: Adds an edge, connecting vertices s and d together
     * @param s a vertex to connect
     * @param d a vertex to connect
     */
    void addEdge(Vertex* s, Vertex* d)
    {
        if (!this->isMultigraph() && s->isNeighbourOf(d))
            throw DuplicateEdge();
        s->addEdge(d);
        if (!this->isDigraph())
            d->addEdge(s);
        // Since by default this isn't multigraph, duplicate edges are not allowed
        /*if (s->isNeighbourOf(d))
            throw DuplicateEdge();
        s->addEdge(d);
        d->addEdge(s);*/
    }

    /**
     * Method: removeEdge
     * ---------------
     * Description: Remove an edge
     * @param s a vertex
     * @param d a vertex
     */
    void removeEdge(Vertex* s, Vertex* d)
    {
        if (!s->isNeighbourOf(d))
            return;
        s->removeEdge(d);
        if (!this->isDigraph())
            d->removeEdge(s);
    }

    /**
     * Method: getVertexById
     * ---------------------
     * Description: informs the number of vertices currently in the graph
     * @param id the vertex id
     * @returns the vertex with the specified id or nullptr if no vertex has the specified id
     */
    Vertex* getVertexById(VertexId id) const
    {
        return VertexFinder<Vertex, VertexContainer>::find(id, vertices);
    }

    /**
     * Method: getMinVertexId
     * ----------------------
     * Description: obtains the minimum vertex id in the graph.
     * @return the minimum vertex id in the graph
     */
    VertexId getMinVertexId() const
    {
        VertexId currMin = UINT_MAX;
        VerticesConstIterator it = verticesConstIterator();
        while (!it.end())
        {
            VertexId currId = (*it)->getVertexId();
            if (currId < currMin)
            {
                currMin = currId;
            }
            it++;
        }
        return currMin;
    }

    /**
     * Method: VerticesConstIterator
     * -----------------------------
     * Description: Provides constant forward iterator to the vertices of the graph
     * @returns a constant iterator abstraction to iterate through the vertices of the graph`
     */
    VerticesConstIterator verticesConstIterator() const
    {
        return VerticesConstIterator(vertices);
    }

    /**
     * Method: VerticesIterator
     * ------------------------
     * Description: Provides forward iterator to the vertices of the graph
     * @returns a iterator abstraction to iterate through the vertices of the graph`
     */
    VerticesIterator verticesIterator()
    {
        return VerticesIterator(vertices);
    }

    /**
     * Method: verticesCount
     * ---------------------
     * Description: informs the number of vertices currently in the graph
     * @returns number of vertices in the graph
     */
    unsigned int verticesCount() const
    {
        return vertices.size();
    }

    int hops(Vertex* vertex1, Vertex* vertex2)
    {
        int hops = 0;
        bool keepTraversing = true;
        std::queue<Vertex*> queue;
        queue.push(vertex1);
        vertex1->setVisited(true);

        while (!queue.empty() && keepTraversing)
        {
            Vertex* vertex = queue.front();
            queue.pop();
            hops++;

            auto it = vertex->neighborsIterator();

            while (!it.end() && keepTraversing)
            {
                Vertex* neighbour = *it;
                if (!neighbour->getVisited())
                {
                    queue.push(neighbour);
                    neighbour->setVisited(true);
                    if (neighbour->getVertexId() == vertex2->getVertexId())
                        keepTraversing = false;
                }
                it++;
            }
        }
        return hops - 1;
    }

    bool isDigraph()
    {
        return this->_isDigraph;
    }

    bool isMultigraph()
    {
        return this->_isMultigraph;
    }

private:
    bool _isDigraph;
    bool _isMultigraph;
    VertexContainer vertices;
};
}  // namespace graphpp
