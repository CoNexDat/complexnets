// This toolbox is licensed under the Academic Free License 3.0.
// Instituto Tecnológico de Buenos Aires (ITBA).

#pragma once

#include "ComplexNets/Position.h"

class NearestNeighbor
{
public:
    void insert(unsigned id, Position pos);
    void remove(unsigned id);
    unsigned get(unsigned id);
};
