#pragma once

//PlainNode is a node for an undirected and unweighted graph
#include "IShellIndexNode.h"

namespace graphpp
{
    class WeightedNode: public INode {

    public:

        WeightedNode(WeightedVertex v, ShellIndexType type){
            shellIndexType = type;
            vertex = &v;
            currentDegree =  (int)(v->strength()) +1;
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

    private:
        int currentDegree;
    };

}  // namespace graphpp
