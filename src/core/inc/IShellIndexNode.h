#pragma once

#include "typedefs.h"

namespace graphpp
{
    enum ShellIndexType {
        // For an graph not directed or weighted
                ShellIndexTypeSimple,
        // For a directed graph, calculates the (k,0)-core for non empty shells
                ShellIndexTypeInDegree,
        // For a directed graph, calculates the (0,l)-core for non empty shells
                ShellIndexTypeOutDegree,
        // For a weighted graph, calculates the shell index binning by equal population (x axe)
                ShellIndexTypeWeightedEqualPopulation,
        // For a weighted graph, calculates the shell index binning by equal population (y axe)
                ShellIndexTypeWeightedEqualStrength
    };

    class INode {
    public:
        ShellIndexType shellIndexType;

        // getDegree returns the current "bin" for the node to be inserted in, the current shell index
        virtual void markAsRemove()  = 0;
        virtual int getDegree()  = 0;
        virtual int decreaseDegree()  = 0;
        virtual NeighbourConstIterator getNeighboursIterator()  = 0;
        virtual unsigned int getVertexId() = 0;

        virtual ~INode() {}
    };
}; // namespace graphpp
