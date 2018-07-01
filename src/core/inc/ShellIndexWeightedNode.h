#pragma once

//PlainNode is a node for an undirected and unweighted graph
#include "IShellIndexNode.h"

namespace graphpp {
    template<class Graph, class Vertex>

    class WeightedNode : public INode<Graph, Vertex> {
    public:
        WeightedNode(Vertex *v, ShellIndexType type, std::vector<unsigned int> binLimits) {
           WeightedVertex *weightedVertex= reinterpret_cast<WeightedVertex*>(v);

            vertex = weightedVertex;

            shellIndexType = type;
            currentStrength = vertex->strength();
            weightedBinsLimits = binLimits;
        }

        void markAsRemove() {
            isRemoved = true;
            currentStrength = 0;
        }

        int getDegree() {
            if(isRemoved || currentStrength <=0){
                return 0;
            }
            return strengthToBin();
        };

        int decreaseDegree(unsigned int vertexId) {
            currentStrength -= vertex->edgeWeightByNeighbour(vertexId);
            return getDegree();
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

        int strengthToBin(){
            if(shellIndexType == ShellIndexTypeWeightedEqualStrength){
                int currentBin = 1;
                int binIndex = 0;
                while(weightedBinsLimits.at(currentBin) < currentStrength){
                    currentBin++;
                }
                return currentBin;
            }
            return 0;
        }

        bool isRemoved = false;
        double currentStrength;
        WeightedVertex *vertex;
        ShellIndexType shellIndexType;
        std::vector<unsigned int> weightedBinsLimits;
    };

}  // namespace graphpp
