#pragma once

//PlainNode is a node for an undirected and unweighted graph
#include "IShellIndexNode.h"
#include "WeightedVertexAspect.h"

namespace graphpp {
    template<class Graph, class Vertex>

    class WeightedNode : public INode<Graph, Vertex> {
    public:
        WeightedNode(Vertex *v, ShellIndexType type, std::vector<unsigned int> binLimits) {
            WeightedVertex *weightedVertex = reinterpret_cast<WeightedVertex *>(v);

            vertex = weightedVertex;
            vertexId = vertex->getVertexId();
            shellIndexType = type;
            currentStrength = vertex->getInitialStrength();
            weightedBinsLimits = binLimits;
            neighbourIdsVector = loadNeighbourIdsVector();
        }

        void markAsRemove() {
            isRemoved = true;
            currentStrength = 0;
        }

        int getDegree() {
            if (isRemoved || currentStrength <= 0) {
                return 0;
            }
            return strengthToBin();
        };

        int decreaseDegree(unsigned int vertexId) {
            currentStrength -= vertex->edgeWeightByNeighbour(vertexId);
            return getDegree();
        };


        NeighbourIdsIterator getNeighbourIdsIterator() {
            return neighbourIdsVector;
        }

        unsigned int getVertexId() {
            return vertexId;
        }

    private:

        std::vector<unsigned int> loadNeighbourIdsVector() {
            std::list<unsigned int>* neighbourIds = vertex->getNeighborsIds();
            std::vector<unsigned int> idsVector;

            for (unsigned int neigh : (*neighbourIds)){
                insert_into(idsVector, neigh);
            }

            return idsVector;
        }

        int strengthToBin() {
            if (shellIndexType == ShellIndexTypeWeightedEqualStrength) {
                int currentBin = 1;
                int binIndex = 0;
                while (weightedBinsLimits.at(currentBin) < currentStrength) {
                    currentBin++;
                }
                return currentBin;
            }
            return 0;
        }

        bool isRemoved = false;
        unsigned int vertexId;
        double currentStrength;
        WeightedVertex *vertex;
        ShellIndexType shellIndexType;
        std::vector<unsigned int> weightedBinsLimits;
        std::vector<unsigned int> neighbourIdsVector;
    };

}  // namespace graphpp
