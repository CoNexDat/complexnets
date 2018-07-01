#pragma once

//PlainNode is a node for an undirected and unweighted graph
#include "IShellIndexNode.h"

namespace graphpp {
    template<class Graph, class Vertex>

    class WeightedNode : public INode<Graph, Vertex> {
    public:
        WeightedNode(Vertex *v, ShellIndexType type) {
           WeightedVertex *weightedVertex= reinterpret_cast<WeightedVertex*>(v);

            vertex = weightedVertex;

            shellIndexType = type;
            currentStrength = vertex->strength();
        }

        void markAsRemove() {
            isRemoved = true;
            currentStrength = 0;
        }

        int getDegree() {
            return 3;
        };

        int decreaseDegree() {
            return 3;
        };


        NeighbourIdsIterator getNeighbourIdsIterator() {
            NeighbourConstIterator neighborsIt = vertex->neighborsConstIterator();

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

        bool compareNodes (WeightedVertex* first, WeightedVertex* second)
        {
            return ( first->strength() < second->strength() );
        }

        //TO CALL SORT --> list.sort(compareNodes);

        bool isRemoved = false;
        double currentStrength;
        WeightedVertex *vertex;
        ShellIndexType shellIndexType;
    };

}  // namespace graphpp
