#ifndef GRAPH_WRITER_H
#define GRAPH_WRITER_H

#include <string>

namespace graphpp
{
template <class Graph, class Vertex>
class GraphWriter
{
public:

    typedef std::string FileName;

    void write(const Graph& g, const FileName& file) const = 0;
};
}

#endif
