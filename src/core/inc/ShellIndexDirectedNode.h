#pragma once


//PlainNode is a node for an undirected and unweighted graph
#include "IShellIndexNode.h"

namespace graphpp {
    template <class Graph, class Vertex>

    class DirectedNode : public INode {
    public:
        DirectedNode(Vertex* v, ShellIndexType type) {
            DirectedVertex* directedVertex = static_cast<DirectedVertex*>(v);
            vertex = directedVertex;

            shellIndexType = type;

            if(type == ShellIndexTypeInDegree){
                currentDegree = vertex->inDegree();
            }else{
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

        NeighbourConstIterator getNeighboursIterator(){
            if(shellIndexType  == ShellIndexTypeInDegree){
                return vertex->inNeighborsConstIterator();
            }else{
                return vertex->outNeighborsConstIterator();
            }
        }

        unsigned int getVertexId(){
            return vertex->getVertexId();
        }

    private:
        int currentDegree;
        DirectedVertex *vertex;
    };

}  // namespace graphpp
