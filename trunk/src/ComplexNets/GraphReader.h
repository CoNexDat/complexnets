#ifndef GRAPH_READER_H
#define GRAPH_READER_H

#include <string>

namespace graphpp
{
template <class Graph, class Vertex, class K>
class GraphReader
{
public:

    virtual void read(Graph& g, const K& source) = 0;
};
}

#endif
