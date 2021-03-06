#pragma once

#include "AdjacencyListVertex.h"

namespace graphpp
{
template <class T>
class DirectedVertexAspect : public T
{
public:
    typedef AdjacencyListVertex::Degree Degree;
    typedef AdjacencyListVertex::VertexId VertexId;
    typedef AdjacencyListVertex::VertexContainer VertexContainer;
    typedef AdjacencyListVertex::VerticesConstIterator VerticesConstIterator;
    typedef AdjacencyListVertex::VerticesIterator VerticesIterator;

    DirectedVertexAspect(VertexId id) : T(id) {
        vertexId = id;
    }

    void addEdge(DirectedVertexAspect<T>* other)
    {
        T::template addEdge<DirectedVertexAspect<T>>(other);
        insert_into(outNeighbors, other);
        if(!isAlreadyNeighbor(other->inNeighborsIterator())){
            other->addIncomingEdge(this);
        }
    }

    void addIncomingEdge(DirectedVertexAspect<T>* other)
    {
        insert_into(inNeighbors, other);
        if(!isAlreadyNeighbor(other->outNeighborsIterator())){
            other->addEdge(this);
        }
    }

    void removeEdge(DirectedVertexAspect<T>* v)
    {
        T::template removeEdge<DirectedVertexAspect<T>>(v);
        AdjacencyListVertex* other = static_cast<AdjacencyListVertex*>(v);
        remove_first_from(outNeighbors, v);
        v->removeIncomingEdge(this);
    }

    void removeIncomingEdge(DirectedVertexAspect<T>* v)
    {
        remove_first_from(inNeighbors, v);
    }

    Degree inDegree() const
    {
        return inNeighbors.size();
    }

    Degree outDegree() const
    {
        return outNeighbors.size();
    }

    Degree inOutDegree() const
    {
        return inDegree() + outDegree();
    }

    VerticesConstIterator inNeighborsConstIterator() const
    {
        return VerticesConstIterator(inNeighbors);
    }

    VerticesConstIterator outNeighborsConstIterator() const
    {
        return VerticesConstIterator(outNeighbors);
    }

    VerticesIterator inNeighborsIterator()
    {
        return VerticesIterator(inNeighbors);
    }

    VerticesIterator outNeighborsIterator()
    {
        return VerticesIterator(outNeighbors);
    }

private:
    VertexContainer inNeighbors;
    VertexContainer outNeighbors;
    VertexId vertexId;

    bool isAlreadyNeighbor(VerticesIterator it){

        while (!it.end())
        {
            DirectedVertexAspect* v = static_cast<DirectedVertexAspect*>(*it);

            if (v->getVertexId() == vertexId)
            {
                return true;
            }

            ++it;
        }
    }

};
}  // namespace graphpp
