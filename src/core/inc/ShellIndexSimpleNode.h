#pragma once

//PlainNode is a node for an undirected and unweighted graph
namespace graphpp
{
    class SimpleNode : public INode {

    public:

        SimpleNode(Vertex *v, ShellIndexType type){
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

        NeighbourConstIterator getNeighboursIterator(){
            return vertex->neighborsConstIterator();
        }

        unsigned int getVertexId(){
            return vertex->getVertexId();
        }


    private:
        int currentDegree;
        Vertex *vertex;
    };

}  // namespace graphpp
