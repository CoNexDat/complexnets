#pragma once

#include "IShellIndex.h"
#include "IShellIndexNode.h"
#include "ShellIndexSimpleNode.h"
#include "ShellIndexDirectedNode.h"
#include "ShellIndexWeightedNode.h"
#include "typedefs.h"

namespace graphpp {

    template<class Graph, class Vertex>
    class ShellIndex : public IShellIndex<Graph, Vertex> {
    public:
        typedef typename IShellIndex<Graph, Vertex>::ShellIndexContainer ShellIndexContainer;
        typedef typename IShellIndex<Graph, Vertex>::ShellIndexIterator ShellIndexIterator;

        ShellIndex(Graph &g, ShellIndexType type) {
            shellIndexType = type;
            totalVertexes = initMap(g);
            if (type == ShellIndexTypeWeightedEqualStrength) {
                getEqualStrengthBinning(g);
            } else if (type == ShellIndexTypeWeightedEqualPopulation) {
                getEqualPopulationBinning(g);
            }
            initMultimapSet(g, type);
            calculateShellIndex();
        }

        virtual ShellIndexIterator iterator() {
            return ShellIndexIterator(shellIndex);
        }

    private:


        INode<Graph, Vertex> *getNextNode() {
            int iterationLimit = totalVertexes;
            if (shellIndexType == ShellIndexTypeWeightedEqualStrength) {
                iterationLimit = weightedEqualStrengthBins;
            }

            for (int i = 0; i < iterationLimit; i++) {
                if (!nodesByCurrentDegree[i].empty()) {
                    return nodesByCurrentDegree[i].front();
                }
            }
            return nullptr;
        }

        void calculateShellIndex() {
            int k = 0;
            // While there are remaining vertices in the graph
            // Select the vertex with the lowest current degree
            while (getNextNode() != nullptr) {
                INode<Graph, Vertex> *nextNode = getNextNode();
                int degree = nextNode->getDegree();

                // If the degree is higher than k, then we have a new higher k-core
                // If lower, then it belongs to the actual k-core
                if (degree > k) {
                    k = degree;
                }
                // Setting the coreness as the current k.
                shellIndex[nextNode->getVertexId()] = k;
                // Will mark it as removed from the structure, since the coreness is already calculated
                nodesByVertexId[nextNode->getVertexId()]->markAsRemove();
                nodesByCurrentDegree[degree].remove(nextNode);
                NeighbourIdsIterator neighborsIt = nextNode->getNeighbourIdsIterator();
                // Iterate through each of it's neighbors to reduce their degree by 1, since v was
                // removed.
                for (auto neighbourId: neighborsIt) {
                    // Get the vertex node to be able to lower it one level in the structure
                    INode<Graph, Vertex> *neighNode = nodesByVertexId[neighbourId];

                    if (neighNode->getDegree() > 0) {
                        // Remove it from the current level
                        nodesByCurrentDegree[neighNode->getDegree()].remove(neighNode);
                        neighNode->decreaseDegree(nextNode->getVertexId());

                        if (neighNode->getDegree() > 0) {
                            // Re add it to a lower level if it still has a valid degree
                            nodesByCurrentDegree[neighNode->getDegree()].push_back(neighNode);
                        } else {
                            // Remove it and set coreness if the degree dropped to 0
                            shellIndex[neighNode->getVertexId()] = k;
                        }
                    }
                }
            }
        }

        int initMap(Graph &g) {
            VerticesConstIterator it = g.verticesConstIterator();
            int total = 0;

            // initialize all elements in zero
            while (!it.end()) {
                Vertex *v = *it;
                shellIndex.insert(
                        std::pair<typename Vertex::VertexId, unsigned int>(v->getVertexId(), 0));
                ++it;
                total++;
            }

            return total;
        }

        void initMultimapSet(Graph &g, ShellIndexType type) {
            VerticesConstIterator it = g.verticesConstIterator();
            nodesByVertexId = new INode<Graph, Vertex> *[totalVertexes + 1];  // will not use index 0

            if (type == ShellIndexTypeWeightedEqualPopulation || type == ShellIndexTypeWeightedEqualStrength) {
                nodesByCurrentDegree =
                        new std::list<INode<Graph, Vertex> *>[totalVertexes > weightedEqualStrengthBins ? totalVertexes
                                                                                                        : weightedEqualStrengthBins];
            } else {
                nodesByCurrentDegree =
                        new std::list<INode<Graph, Vertex> *>[totalVertexes];
            }
            // initialize all elements using the vertex id and the vertex degree
            while (!it.end()) {
                Vertex *v = *it;
                INode<Graph, Vertex> *newNode = getNodeFromType(v, type);//new Node();
                nodesByVertexId[newNode->getVertexId()] = newNode;
                unsigned int nodeDegree = (unsigned int) (newNode->getDegree());
                nodesByCurrentDegree[nodeDegree].push_back(newNode);
                ++it;
            }
        }

        INode<Graph, Vertex> *getNodeFromType(Vertex *v, ShellIndexType type) {
            switch (type) {
                case ShellIndexTypeWeightedEqualStrength:{
                    return new WeightedNode<Graph, Vertex>(v, type, weightedBinsLimitsEqStrength);
                }
                case ShellIndexTypeWeightedEqualPopulation: {
                    return new WeightedNode<Graph, Vertex>(v, type, weightedBinsLimitsEqPopulation);
                }
                case ShellIndexTypeInDegree:
                case ShellIndexTypeOutDegree: {
                    return new DirectedNode<Graph, Vertex>(v, type);
                }
                default:{
                    return new SimpleNode<Graph, Vertex>(v, type);
                }
            }
        }

        void getEqualStrengthBinning(Graph g) {
            VerticesConstIterator it = g.verticesConstIterator();
            double maxStrength = 0;
            while (!it.end()) {
                WeightedVertex *weightedVertex = reinterpret_cast<WeightedVertex *>(*it);
                if (weightedVertex->getInitialStrength() > maxStrength) {
                    maxStrength = weightedVertex->getInitialStrength();
                }
                ++it;
            }
            weightedBinsLimitsEqStrength   = new std::vector<double>(0);
            for (double bin = 1; bin <= weightedEqualStrengthBins; bin++) {
                // In case the bucket is at a double value, it is casted to the closest integer
                weightedBinsLimitsEqStrength->push_back(maxStrength * bin / weightedEqualStrengthBins);
            }
        }

        void getEqualPopulationBinning(Graph g) {
            std::vector<WeightedVertex *> *weightedVertexVector = new std::vector<WeightedVertex *>(0);
            VerticesConstIterator it = g.verticesConstIterator();
            while (!it.end()) {
                WeightedVertex *weightedVertex = reinterpret_cast<WeightedVertex *>(*it);
                weightedVertexVector->push_back(weightedVertex);
                ++it;
            }

            std::sort(weightedVertexVector->begin(), weightedVertexVector->end(), weightedVertexComparator);

            weightedBinsLimitsEqPopulation = new std::vector<double>(0);
            for (double bin = 1; bin < weightedEqualStrengthBins; bin++) {
                unsigned int borderVertexIndex =  (totalVertexes * bin / weightedEqualStrengthBins);
                weightedBinsLimitsEqPopulation->push_back(
                        (unsigned int) (weightedVertexVector->at(borderVertexIndex)->getInitialStrength()));
            }
        }

        struct {
            bool operator()(WeightedVertex *first, WeightedVertex *second) const{
                return (first->getInitialStrength() < second->getInitialStrength());
            }
        }weightedVertexComparator;


        //TO CALL SORT --> list.sort(compareNodes);

        typedef typename Graph::VerticesConstIterator VerticesConstIterator;

        // This container will be set with the coreness of each vertex when found.
        ShellIndexContainer shellIndex;

        // This structure represents an array of node pointers.
        // This nodes are the different node-vertexes in the main structure
        // The index of the array represents the id of the node.
        // Used to get the node structure in O(1), to allow it to be moved to another list.
        INode<Graph, Vertex> **nodesByVertexId;
        // This is the main structure, contains an array of linked lists.
        // The index of the array represents the current degree of the vertexes stored on that list.
        // The lists are doubly-linked lists to allow a node representation to be easily removed.
        std::list<INode<Graph, Vertex> *> *nodesByCurrentDegree;
        int totalVertexes;
        std::vector<double> * weightedBinsLimitsEqStrength;
        std::vector<double> * weightedBinsLimitsEqPopulation;

        const int weightedEqualStrengthBins = 10;

        ShellIndexType shellIndexType;
    };
}  // namespace graphpp
