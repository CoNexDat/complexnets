#pragma once


//PlainNode is a node for an undirected and unweighted graph
#include "IShellIndexNode.h"

namespace graphpp {
    template<class Graph, class Vertex>

    class DirectedNode : public INode<Graph, Vertex> {
    public:
        DirectedNode(Vertex *v, ShellIndexType type) {
            DirectedVertex *directedVertex = static_cast<DirectedVertex *>(v);
            vertex = directedVertex;

            shellIndexType = type;

            if (type == ShellIndexTypeInDegree) {
                currentDegree = vertex->inDegree();
            } else {
                currentDegree = vertex->outDegree();
            }
        }

        void markAsRemove() {
            currentDegree = 0;
        }

        int getDegree() {
            return currentDegree;
        };

        int decreaseDegree() {
            currentDegree--;
            return currentDegree;
        };


        NeighbourIdsIterator getNeighbourIdsIterator() {
            NeighbourConstIterator neighborsIt = getIterator();


            std::vector<unsigned int> idsVector;
            while (!neighborsIt.end()) {
                AdjacencyListVertex *neigh = *neighborsIt;
                insert_into(idsVector, neigh->getVertexId());
                ++neighborsIt;
            }

            return idsVector;
        }



        unsigned int getVertexId() {
            return vertex->getVertexId();
        }

    private:
        NeighbourConstIterator getIterator() {
            if (shellIndexType == ShellIndexTypeOutDegree) {
                return vertex->outNeighborsConstIterator();
            }
            return vertex->inNeighborsConstIterator();
        }

        int currentDegree;
        DirectedVertex *vertex;
        ShellIndexType shellIndexType;
    };

}  // namespace graphpp
