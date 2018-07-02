#pragma once

//PlainNode is a node for an undirected and unweighted graph
#include "IShellIndexNode.h"
#include "WeightedVertexAspect.h"

namespace graphpp {
    template<class Graph, class Vertex>

    class WeightedNode : public INode<Graph, Vertex> {
    public:
        WeightedNode(Vertex *v, ShellIndexType type, std::vector<double> *binLimits) {
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
            if (isRemoved) {
                return 0;
            }
            return strengthToBin();
        };

        int decreaseDegree(unsigned int vertexId) {
            double edgeWeight = vertex->getNeighbourWeight(vertexId);
            currentStrength -= edgeWeight;
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
            std::list<unsigned int> *neighbourIds = vertex->getNeighborsIds();
            std::vector<unsigned int> idsVector;

            for (unsigned int neigh : (*neighbourIds)) {
                insert_into(idsVector, neigh);
            }

            return idsVector;
        }

        int strengthToBin() {
            int currentBin = 1;
            while (currentStrength > weightedBinsLimits->at(currentBin) ) {
                currentBin++;
            }
            return currentBin;
        }

        bool isRemoved = false;
        unsigned int vertexId;
        double currentStrength;
        WeightedVertex *vertex;
        ShellIndexType shellIndexType;
        std::vector<double> *weightedBinsLimits;
        std::vector<unsigned int> neighbourIdsVector;
    };

}  // namespace graphpp
