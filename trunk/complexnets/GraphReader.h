#ifndef GRAPH_READER_H
#define GRAPH_READER_H

#include <string>

namespace graphpp
{
    template <class Graph, class Vertex>
    class GraphReader
    {
        public:
            
            typedef std::string FileName;
            
            void read(Graph& g, const FileName& file) const = 0;
    };
}

#endif
