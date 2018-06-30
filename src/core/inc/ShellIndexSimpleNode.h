#pragma once

//PlainNode is a node for an undirected and unweighted graph
namespace graphpp {

    template<class Graph, class Vertex>
    class SimpleNode : public INode<Graph, Vertex> {
    public:

        SimpleNode(Vertex *v, ShellIndexType type) {
            vertex = v;
            shellIndexType = type;
            currentDegree = v->degree();
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
        int currentDegree;
        Vertex *vertex;
        ShellIndexType shellIndexType;
    };

}  // namespace graphpp
