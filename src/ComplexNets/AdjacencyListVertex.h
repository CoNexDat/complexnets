// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).
// Last modification: December 19th, 2012.

#ifndef ADJACENCY_LIST_VERTEX_H
#define ADJACENCY_LIST_VERTEX_H

#include <set>
#include "mili/mili.h"

namespace graphpp
{
/**
* Class: AdjacencyListVertex
* --------------------------
* Description: Principal Vertex class for adjacency list unweighted and undirected graphs
*/
class AdjacencyListVertex
{
public:
    typedef unsigned int VertexId;
    typedef unsigned int Degree;

    typedef std::vector<AdjacencyListVertex*> VertexContainer;
    typedef CAutonomousIterator<VertexContainer> VerticesConstIterator;
    typedef AutonomousIterator<VertexContainer> VerticesIterator;

    AdjacencyListVertex(VertexId id) : vertexId(id), visited(false)
    {
    }

    /**
    * Method: addEdge
    * --------------------------
    * Description: Adds an edge, particularly a vertex to the list of
    * the vertex's neighbors
    * @param v Vertex neighbour to be added
    */
    template <class T>
    void addEdge(T* v)
    {
        AdjacencyListVertex* other = static_cast<AdjacencyListVertex*>(v);
        insert_into(neighbors, other);
    }

    /**
    * Method: removeEdge
    * --------------------------
    * Description: Remove an edge, particularly a vertex from the list of
    * the vertex's neighbors
    * @param v Vertex neighbour to be added
    */
    template <class T>
    void removeEdge(T* v)
    {
        AdjacencyListVertex* other = static_cast<AdjacencyListVertex*>(v);
        remove_first_from(neighbors, other);
    }

    /**
    * Method: neighborsConstIterator
    * ------------------------------
    * Description: Provides a container independent constant iterator
    * to the collection of neighbors
    * @returns CAutonomousIterator for iterating neighbors
    */
    VerticesConstIterator neighborsConstIterator() const
    {
        return VerticesConstIterator(neighbors);
    }

    /**
    * Method: neighborsIterator
    * -------------------------
    * Description: Provides a container-independent mutable iterator to the
    * collection of neighbors
    * @returns AutonomousIterator for iterating neighbors
    */
    VerticesIterator neighborsIterator()
    {
        return VerticesIterator(neighbors);
    }

    /**
    * Method: isNeighbourOf
    * ----------------------
    * Description: Indicates whether the other vertex is a known neighbor
    * @param other Vertex that we want to test if is a neighbour
    * @returns True if the vertex is a neighbour, and false otherwise
    */
    bool isNeighbourOf(AdjacencyListVertex* other) const
    {
        return contains(neighbors, other);
    }

    /**
    * Method: degree
    * --------------
    * Description: returns the degree of the Vertex, measured as the number of
    * neighbours it has
    * @returns The degree of the vertex
    */
    Degree degree() const
    {
        return neighbors.size();
    }

    /**
    * Method: getVertexId
    * -------------------
    * Description: returns the Id of the current vertex. The id of a vertex acts
    * as a unique identifier
    * @returns vertex's id
    */
    VertexId getVertexId() const
    {
        return vertexId;
    }

    bool operator<(const AdjacencyListVertex& other) const
    {
        return getVertexId() < other.getVertexId();
    }

    // These two methods shall be removed, and changed for a map in algorithms,
    // or passed to an aspect of the vertex if needed
    bool getVisited() const
    {
        return visited;
    }

    void setVisited(bool v)
    {
        visited = v;
    }

private:
    VertexContainer neighbors;
    VertexId vertexId;
    bool visited;
};
}

#endif
